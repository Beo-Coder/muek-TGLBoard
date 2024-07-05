//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_DISPLAY_PROGRAM_H
#define TGL_BOARD_DISPLAY_PROGRAM_H

class MatrixOutput;
class Color;

#include "PIOMatrixOutput/pio_matrix_output.h"

class DisplayProgram {

protected:
    Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH];
    MatrixOutput *matrix;

public:
    DisplayProgram(MatrixOutput *matrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);


    uint32_t refreshSpeed;

    void clearFrame();



    virtual void button1ISR(bool state) = 0;
    virtual void button2ISR(bool state) = 0;

    virtual void refresh() = 0;
    virtual void restart() = 0;

    virtual void exit();


};











#endif //TGL_BOARD_DISPLAY_PROGRAM_H
