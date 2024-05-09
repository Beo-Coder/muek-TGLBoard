//
// Created by Leo Baschang on 02.03.24.
//

#ifndef UNTITLED24_PIOMATRIXOUTPUT_H
#define UNTITLED24_PIOMATRIXOUTPUT_H

#include <Arduino.h>
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/watchdog.h"
#include "hardware/timer.h"
#include "hardware/sync.h"
#include "pio_program.pio.h"
#include "color.h"


#define MATRIX_LENGTH 16
#define MATRIX_HEIGHT 8


#define MATRIX_SUBMATRIX_COUNT 2


#define MATRIX_SIZE (MATRIX_LENGTH*MATRIX_HEIGHT)
#define MATRIX_SUBMATRIX_SIZE (MATRIX_SIZE/MATRIX_SUBMATRIX_COUNT)


#define MAX_FRAMES_IN_BUFFER 10
#define MAX_SUBFRAMES 8

#define TIMER_INDEX 1

#define dataSendTime 1950 // in µs
#define subframePauseIntervall 350 // in µs (must be at least 150 (probably more))


class MatrixOutput {

    uint32_t matrix[MATRIX_SUBMATRIX_COUNT][MATRIX_SUBMATRIX_SIZE];

    uint32_t sendMatrix[MATRIX_SIZE];


    PIO pio;
    uint8_t sm;
    uint8_t dmaChannel;

    dma_channel_config dmac;

    uint32_t lastSendData;


    uint32_t frameBuffer[MAX_FRAMES_IN_BUFFER + 1][MAX_SUBFRAMES][MATRIX_SIZE * 3 / 4];
    uint8_t frameBufferWriteIndex;
    uint8_t frameBufferReadIndex;
    uint8_t frameBufferLength;
    boolean frameBufferEnable;
    uint32_t frameBufferInterval;

    uint8_t subframeBufferIndex;
    boolean subframeBufferEnable;
    boolean firstSubframe;


    uint32_t timerFrameCount;

    bool timerSubframeCountEnable;
    uint32_t timerSubframeCount;

    static void enableTimer(boolean enable = true);

    static void setTimer();



    void createFrame(uint32_t (*display)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t index, uint8_t subframeIndex);

    void createFrame(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t index, uint8_t subframeIndex);

    void sendFrame(uint8_t frameBufferIndex, uint8_t subframeIndex);


public:
    void calcSubframes(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t index);


    void internalDmaHandler();

    void internalTimerHandler();


    MatrixOutput(PIO pio, uint8_t sm, uint8_t dmaChannel, uint8_t pin_1, uint8_t pin_2);

    void setDisplayData(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void addToFrameBuffer(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    uint8_t getFreeFrames() const;

    void enableFrameBuffer(boolean enable = true);

    void setFrameBufferInterval(uint32_t interval);

    void enableSubframes(boolean enable = true);


    void clearDisplay();

    void sendData();

};


// static Timer Handler
void timerHandler();

// "Lookup "Table"" for Timer
static MatrixOutput *instancesTimer;


// static DMA Handler
void dmaHandler();

// IRQ DMA "LookUp Table"
static MatrixOutput *instancesDMA[16]; // index is DMA Channel




#endif //UNTITLED24_PIOMATRIXOUTPUT_H
