//
// Created by leo on 25.05.24.
//
#include "animations.h"
#include "PIOMatrixOutput/pio_matrix_output.h"

const Color darkPurple(NORMAL_BRIGHTNESS*2,0,NORMAL_BRIGHTNESS);
const Color* jumpAnimationColorIndex[] ={&colorBlank, &darkPurple, &colorCyan};

const uint8_t jumpAnimationFrames[][MATRIX_HEIGHT][MATRIX_LENGTH] = {
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,2,0,0,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,2,0,0,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,2,0,0,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,2,0,0,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,2,0,0,2, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,2,0,0,2, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,2,2,1,2, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,2,0,0,2,2, 0,0,0,0,0},
        },

        {
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0,2},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,1,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,1,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 1,2,2,1,1,1,2,2},
                {0,0,0,0,0,0,0,0, 1,1,1,1,1,1,0,0},
                {0,0,0,0,0,0,0,0, 1,2,2,1,1,1,0,0},
                {0,0,0,0,0,0,0,0, 1,1,2,1,1,1,0,0},
                {0,0,0,0,0,0,0,0, 1,1,1,1,1,1,2,2},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0,2},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,1,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,1,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 1,2,2,1,1,1,2,2},
                {0,0,0,0,0,0,0,0, 1,1,1,1,1,1,0,0},
                {0,0,0,0,0,0,0,0, 1,2,2,1,1,1,0,0},
                {0,0,0,0,0,0,0,0, 1,1,2,1,1,1,0,0},
                {0,0,0,0,0,0,0,0, 1,1,1,1,1,1,2,2},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0,2},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,1,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,1,0},
                {0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0,0},
        },
        {
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,2,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,2,1,0},
                {0,0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,1,1,1,2},
                {0,0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0},
        },

        {
                {0,0,0,0,0, 0,2,0,0,2,0, 0,0,0,0,0},
                {0,0,0,0,0, 0,2,0,0,2,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,2,1,2,2,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,2,1,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0, 2,2,0,0,2,2, 0,0,0,0,0},
                {0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0, 2,2,0,0,2,2, 0,0,0,0,0},
                {0,0,0,0,0, 0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},

        },
        {
                {0,0,0,0,0, 2,2,0,0,2,2, 0,0,0,0,0},
                {0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0, 0,2,0,0,2,0, 0,0,0,0,0},
                {0,0,0,0,0, 0,2,0,0,2,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,2,1,2,2,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,2,1,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0, 2,2,0,0,2,2, 0,0,0,0,0},
                {0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0, 2,2,0,0,2,2, 0,0,0,0,0},
                {0,0,0,0,0, 0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},

        },
        {
                {0,0,0,0,0, 2,2,0,0,2,2, 0,0,0,0,0},
                {0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0, 0,2,0,0,2,0, 0,0,0,0,0},
                {0,0,0,0,0, 0,2,0,0,2,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,2,1,2,2,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,2,1,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,0,1,1,1,1,1, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0, 2,2,0,0,2,2, 0,0,0,0,0},
                {0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
        },
        {
                {0,0,0,0,0, 2,2,0,0,2,2, 0,0,0,0,0},
                {0,0,0,0,0, 0,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0, 1,1,1,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,2,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,2,1,2,1,1,1, 0,0,0,0,0},
                {0,0,0,0,0 ,1,1,1,1,1,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0 ,0,0,0,0,0,0, 0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0},
                {0,1,1,2,1,1, 0,0,0,0,0,0,0,0,0,0},
                {0,1,1,2,2,1, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0},
                {2,0,1,2,2,1, 0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,1,1,1, 0,0,0,0,0,0,0,0},
                {2,2,1,1,1,2,1,1, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,2,2,1, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,1,1,1, 0,0,0,0,0,0,0,0},
                {2,2,1,1,1,2,2,1, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0},
                {0,1,1,2,1,1, 0,0,0,0,0,0,0,0,0,0},
                {0,1,1,2,2,1, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0},
                {2,0,1,2,2,1, 0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,1,1,1, 0,0,0,0,0,0,0,0},
                {2,2,1,1,1,2,1,1, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,2,2,1, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,1,1,1, 0,0,0,0,0,0,0,0},
                {2,2,1,1,1,2,2,1, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0},
                {0,1,1,2,1,1, 0,0,0,0,0,0,0,0,0,0},
                {0,1,1,2,2,1, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0},
                {2,0,1,2,2,1, 0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,0,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,1,1,1,0, 0,0,0,0,0,0,0,0,0,0},
                {2,1,2,2,1,0, 0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

        },
        {
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,1,1,1, 0,0,0,0,0,0,0,0},
                {2,2,1,1,1,2,1,1, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,2,2,1, 0,0,0,0,0,0,0,0},
                {0,0,1,1,1,1,1,1, 0,0,0,0,0,0,0,0},
                {2,2,1,1,1,2,2,1, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0},

        },
};