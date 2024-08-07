//
// © 2024 Leonhard Baschang
//

#include "pio_matrix_output.h"
#include "pio_program.pio.h"
#include "color.h"

void timerHandler() {
    if (timer_hw->ints == 1 << TIMER_INDEX) {
        instancesTimer->internalTimerHandler();

        uint64_t target = timer_hw->timerawl + 10; // 10 us
        timer_hw->alarm[TIMER_INDEX] = (uint32_t) target;
        hw_clear_bits(&timer_hw->intr, 1u << TIMER_INDEX);
    }

}

void dmaHandler() {

    // get DMA channel which caused IRQ
    for (uint8_t i = 0; i < 16; i++) {
        if (dma_channel_get_irq0_status(i)) {
            instancesDMA[i]->internalDmaHandler();
            // clear IRQ
            dma_hw->ints0 = 1u << i;
        }
    }

}

void MatrixOutput::internalTimerHandler() {

    if (frameBufferEnable) {
        timerFrameCount++;
        if ((timerFrameCount >= (frameBufferInterval * 1000 / 10)) && frameBufferInterval != 0 && (getFreeFrames() < MAX_FRAMES_IN_BUFFER-1) ) {
            timerFrameCount = 0;
            frameBufferReadIndex = (frameBufferReadIndex + 1) % MAX_FRAMES_IN_BUFFER;
            frameBufferLength--;
            if (!subframeBufferEnable) {
                sendFrame(frameBufferReadIndex, subframeBufferIndex);
            }


        }

    }

    if (subframeBufferEnable && timerSubframeCountEnable) {

        if ((timerSubframeCount >= (subframePauseIntervall / 10) )) {

            timerSubframeCount = 0;
            timerSubframeCountEnable = false;

            sendFrame(frameBufferReadIndex, subframeBufferIndex);

            subframeBufferIndex = (subframeBufferIndex + 1) % MAX_SUBFRAMES;

            
        }
        if(timer_hw->timerawl - lastSendData >= dataSendTime){
            timerSubframeCount++;
        }

    }


}


void MatrixOutput::internalDmaHandler() {
    if (subframeBufferEnable) {
        timerSubframeCount = 0;
        timerSubframeCountEnable = true;
    }

}


MatrixOutput::MatrixOutput(PIO pio, uint8_t sm, uint8_t dmaChannel, uint8_t pin_1, uint8_t pin_2) {
    this->pio = pio;
    this->sm = sm;
    this->dmaChannel = dmaChannel;

    timerFrameCount = 0;
    timerSubframeCount = 0;


    // get offset of pio program
    uint offset = pio_add_program(pio, &argb_program);


    //init pio state machine
    argb_program_init(pio, sm, offset, pin_1, pin_2, 32);

    // init dma
    dmac = dma_channel_get_default_config(dmaChannel);

    channel_config_set_transfer_data_size(&dmac, DMA_SIZE_32);
    channel_config_set_read_increment(&dmac, true);
    channel_config_set_write_increment(&dmac, false);

    channel_config_set_irq_quiet(&dmac, false);

    channel_config_set_dreq(&dmac, pio_get_dreq(pio, sm, true));

    dma_channel_configure(dmaChannel,
                          &dmac,
                          &pio->txf[0], // Destination pointer
                          frameBuffer[0][0], // Source pointer (Here not relevant)
                          MATRIX_SIZE * 3 / 4, // Number of transfers
                          false // Dont start yet
    );

    // IRQ on DMA completion
    dma_channel_set_irq0_enabled(dmaChannel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dmaHandler);
    irq_set_enabled(DMA_IRQ_0, true);

    // Dont start PIO yet
    pio_sm_set_enabled(pio, sm, false);




    // Timer for frames and subframes
    hw_set_bits(&timer_hw->inte, 1u << TIMER_INDEX);
    irq_set_exclusive_handler(TIMER_INDEX, timerHandler);
    irq_set_enabled(TIMER_INDEX, false);

    uint64_t target = timer_hw->timerawl + 10; // 10 us
    timer_hw->alarm[TIMER_INDEX] = (uint32_t) target;


    lastSendData = 0;


    frameBufferWriteIndex = 0;
    frameBufferReadIndex = 0;
    frameBufferLength = 0;
    frameBufferEnable = false;
    frameBufferInterval = 100;

    subframeBufferIndex = 0;
    subframeBufferEnable = false;
    firstSubframe = false;


    instancesDMA[dmaChannel] = this;
    instancesTimer = this;


}

void MatrixOutput::enableTimer(bool enable) {
    irq_set_enabled(TIMER_INDEX, enable);
    setTimer();
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_INDEX);
}

void MatrixOutput::setTimer() {
    uint64_t target = timer_hw->timerawl + 10; // 10 us
    timer_hw->alarm[TIMER_INDEX] = (uint32_t) target;
}




void
MatrixOutput::createFrame(uint32_t (*display)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t index, uint8_t subframeIndex) {

    // Create matrix, where the first index is submatrix, and the second index is led in this submatrix
    for (int i = 0; i < MATRIX_SIZE; i++) {
        matrix[i / MATRIX_SUBMATRIX_SIZE][i % MATRIX_SUBMATRIX_SIZE] = (*display)[i / MATRIX_LENGTH][i % MATRIX_LENGTH];
    }

    // Create matrix, where the first index is the index in the framebuffer,
    // second index is subframe index,
    // third index is points to a filled 32 bit value with color data.
    // Every second bit is for one submatrix.
    // Bits: 12121212121212...; 1: bit for first submatrix; 2: bit for seconds submatrix
    uint32_t bitsShifted = 0;
    for (int i = 0; i < MATRIX_SUBMATRIX_SIZE; i++) {
        for (int j = 23; j >= 0; j--) {
            for (int k = 0; k < MATRIX_SUBMATRIX_COUNT; k++) {
                frameBuffer[index][subframeIndex][bitsShifted / 32] = (frameBuffer[index][subframeIndex][bitsShifted / 32] << 1) | ((matrix[MATRIX_SUBMATRIX_COUNT - 1 - k][i] >> (j) & 0x01));
                bitsShifted++;

            }
        }
    }



}

void MatrixOutput::createFrame(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t index, uint8_t subframeIndex) {
    uint32_t outputMatrix[MATRIX_HEIGHT][MATRIX_LENGTH];
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_LENGTH; j++) {
            outputMatrix[i][j] = (*display)[i][j].calc();

        }
    }
    createFrame(&outputMatrix, index, subframeIndex);
}




void MatrixOutput::setDisplayData(Color (*displayData)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    addToFrameBuffer(displayData);


}

void MatrixOutput::addToFrameBuffer(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    if (subframeBufferEnable) {
        calcSubframes(display, frameBufferWriteIndex);
    } else {
        subframeBufferIndex = 0;
        createFrame(display, frameBufferWriteIndex, 0);
    }

    if (frameBufferEnable) {
        frameBufferWriteIndex = (frameBufferWriteIndex + 1) % MAX_FRAMES_IN_BUFFER;
        frameBufferLength++;
    }


}

uint8_t MatrixOutput::getFreeFrames() const {
    return MAX_FRAMES_IN_BUFFER - frameBufferLength;
}


void MatrixOutput::enableFrameBuffer(bool enable) {
    frameBufferEnable = enable;



    if (enable) {
        enableTimer();
        frameBufferReadIndex = frameBufferWriteIndex;
        sendFrame(frameBufferReadIndex, subframeBufferIndex);

    } else if (!subframeBufferEnable) {
        enableTimer(false);
    }


}

void MatrixOutput::setFrameBufferInterval(uint32_t interval) {
    frameBufferInterval = interval;
}

void MatrixOutput::enableSubframes(bool enable) {
    subframeBufferEnable = enable;

    if (enable) {
        firstSubframe = true;
        dma_hw->ints0 = 1u << dmaChannel;

        enableTimer();

    } else if (!frameBufferEnable) {
        enableTimer(false);
    }

}


void MatrixOutput::clearDisplay() {
    enableFrameBuffer(false);
    enableSubframes(false);

    uint32_t outputMatrix[MATRIX_HEIGHT][MATRIX_LENGTH];
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_LENGTH; j++) {
            outputMatrix[i][j] = 0x00;
        }
    }

    createFrame(&outputMatrix, 0, 0);
    sendFrame(0, 0);
}

void MatrixOutput::sendFrame(uint8_t frameBufferIndex, uint8_t subframeIndex) {

    while(time_us_64() - lastSendData <  dataSendTime);

    dma_channel_set_read_addr(dmaChannel, &(frameBuffer[frameBufferIndex][subframeIndex]), true);
    pio_sm_set_enabled(pio, sm, true);
    lastSendData = time_us_64();


}

void MatrixOutput::sendData() {


    if((!subframeBufferEnable && !frameBufferEnable) || firstSubframe){
        firstSubframe = false;
        sendFrame(frameBufferReadIndex, subframeBufferIndex);
    }


    if (frameBufferEnable) {
        frameBufferReadIndex = (frameBufferReadIndex + 1) % MAX_FRAMES_IN_BUFFER;
        frameBufferLength--;
    }


}

void MatrixOutput::calcSubframes(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t index) {

    uint32_t outDisplay[MAX_SUBFRAMES][MATRIX_HEIGHT][MATRIX_LENGTH];

    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_LENGTH; j++) {
            for (int k = 0; k < MAX_SUBFRAMES; k++) {
                outDisplay[k][i][j] = 0;
            }

        }
    }

    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_LENGTH; j++) {

            uint8_t baseData[3];
            uint8_t fracData[3];

            baseData[0] = (*display)[i][j].getBlue8Bit();
            baseData[1] = (*display)[i][j].getRed8Bit();
            baseData[2] = (*display)[i][j].getGreen8Bit();


            fracData[0] = (*display)[i][j].getBlueActiveSubframes();
            fracData[1] = (*display)[i][j].getRedActiveSubframes();
            fracData[2] = (*display)[i][j].getGreenActiveSubframes();


            for (int k = 0; k < 3; k++) {
                if (fracData[k] == 0) {
                    outDisplay[0][i][j] |= baseData[k] << (8 * k);
                } else {
                    outDisplay[0][i][j] |= (baseData[k] + 1) << (8 * k);
                }
            }


            for (int subframe = 1; subframe < MAX_SUBFRAMES; subframe++) {
                for (int k = 0; k < 3; k++) {
                    if ((fracData[k] - subframe <= 0)) {
                        outDisplay[subframe][i][j] |= baseData[k] << (8 * k);
                    } else {
                        outDisplay[subframe][i][j] |= (baseData[k] + 1) << (8 * k);
                    }
                }

            }


        }
    }

    // Direct manipulation of frameBufferReadIndex
    // Only because otherwise LEDs behave weird because the frame getting output is overwritten
    if(!frameBufferEnable){
        index = (frameBufferReadIndex + 1) % MAX_FRAMES_IN_BUFFER;
    }
    for (int i = 0; i < MAX_SUBFRAMES; i++) {
        createFrame(&(outDisplay[i]), index, i);
    }
    if(!frameBufferEnable){
        frameBufferReadIndex = (frameBufferReadIndex + 1) % MAX_FRAMES_IN_BUFFER;
    }




}






































