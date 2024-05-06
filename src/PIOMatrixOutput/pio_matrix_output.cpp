//
// Created by Leo Baschang on 02.03.24.
//

#include "pio_matrix_output.h"


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
        timerSubframeCount++;
        if ((timerSubframeCount >= (subframePauseIntervall / 10))) {

            timerSubframeCount = 0;
            timerSubframeCountEnable = false;

            sendFrame(frameBufferReadIndex, subframeBufferIndex);

            subframeBufferIndex = (subframeBufferIndex + 1) % MAX_SUBFRAMES;

            
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

void MatrixOutput::enableTimer(boolean enable) {
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


    for (int i = 0; i < MATRIX_SIZE; i++) {

        matrix[i / MATRIX_SUBMATRIX_SIZE][i % MATRIX_SUBMATRIX_SIZE] = (*display)[i / MATRIX_LENGTH][i % MATRIX_LENGTH];

    }

    int bitsShifted = 0;
    for (int i = 0; i < MATRIX_SUBMATRIX_SIZE; i++) {
        for (int j = 0; j < 24; j++) {
            for (int k = 0; k < MATRIX_SUBMATRIX_COUNT; k++) {
                frameBuffer[index][subframeIndex][bitsShifted / 32] = (frameBuffer[index][subframeIndex][bitsShifted / 32] << 1) | ((matrix[MATRIX_SUBMATRIX_COUNT - 1 - k][i] >> (23 - j) & 0x01));
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


void MatrixOutput::enableFrameBuffer(boolean enable) {
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

void MatrixOutput::enableSubframes(boolean enable) {
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

    while(timer_hw->timelr - lastSendData <  dataSendTime);

    dma_channel_set_read_addr(dmaChannel, &(frameBuffer[frameBufferIndex][subframeIndex]), true);
    pio_sm_set_enabled(pio, sm, true);
    lastSendData = timer_hw->timelr;


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

            baseData[0] = (uint8_t) (*display)[i][j].getBlue();
            baseData[1] = (uint8_t) (*display)[i][j].getRed();
            baseData[2] = (uint8_t) (*display)[i][j].getGreen();



            fracData[0] = (((*display)[i][j].getBlue()) - (float) baseData[0]) * MAX_SUBFRAMES;
            fracData[1] = (((*display)[i][j].getRed()) - (float) baseData[1]) * MAX_SUBFRAMES;
            fracData[2] = (((*display)[i][j].getGreen()) - (float) baseData[2]) * MAX_SUBFRAMES;


            for (int k = 0; k < 3; k++) {
                if (fracData[k] == 0) {
                    outDisplay[0][i][j] |= baseData[k] << (8 * k);
                } else {
                    outDisplay[0][i][j] |= (baseData[k] + 1) << (8 * k);
                }
            }


            for (int subframe = 1; subframe < MAX_SUBFRAMES; subframe++) {
                for (int k = 0; k < 3; k++) {
                    if ((fracData[k] - subframe <= 0.0001)) {
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






































