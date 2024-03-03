//
// Created by Leo Baschang on 02.03.24.
//

#ifndef UNTITLED24_PIOMATRIXOUTPUT_H
#define UNTITLED24_PIOMATRIXOUTPUT_H

#include <Arduino.h>
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "pioARGB.pio.h"

#define MATRIX_LENGTH 16
#define MATRIX_HEIGHT 8


#define MATRIX_SUBMATRIX_COUNT 2


#define MATRIX_SIZE MATRIX_LENGTH*MATRIX_HEIGHT
#define MATRIX_SUBMATRIX_SIZE MATRIX_SIZE/MATRIX_SUBMATRIX_COUNT


struct color {
    uint8_t blue;
    uint8_t red;
    uint8_t green;
};


class MatrixOutput {
    uint32_t sendMatrix[MATRIX_SIZE];

    PIO pio;
    uint8_t sm;
    uint8_t dmaChannel;

    dma_channel_config dmac;


public:
    uint32_t matrix[MATRIX_SUBMATRIX_COUNT][MATRIX_SUBMATRIX_SIZE];

    MatrixOutput(PIO pio, uint8_t sm, uint8_t dmaChannel, uint8_t pin_1, uint8_t pin_2);

    void sendData();
};


#endif //UNTITLED24_PIOMATRIXOUTPUT_H
