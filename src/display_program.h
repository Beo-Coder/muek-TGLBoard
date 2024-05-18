//
// Created by leo on 28.04.24.
//

#ifndef TGL_BOARD_DISPLAY_PROGRAM_H
#define TGL_BOARD_DISPLAY_PROGRAM_H

class MatrixOutput;
class Color;

#include "PIOMatrixOutput/pio_matrix_output.h"

class display_program {

protected:
    Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH];
    MatrixOutput *matrix;

public:
    display_program(MatrixOutput *matrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);


    uint32_t refreshSpeed;

    void clearFrame();



    virtual void button1ISR(bool state) = 0;
    virtual void button2ISR(bool state) = 0;

    virtual void refresh() = 0;
    virtual void restart() = 0;


};











#endif //TGL_BOARD_DISPLAY_PROGRAM_H
