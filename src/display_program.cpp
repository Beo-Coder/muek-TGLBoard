//
// Created by leo on 29.04.24.
//
#include "display_program.h"
#include "PIOMatrixOutput/pio_matrix_output.h"

DisplayProgram::DisplayProgram(MatrixOutput *matrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    this->matrix = matrix;
    this->frame = frame;
}

void DisplayProgram::clearFrame() {
    for(int i=0; i<MATRIX_HEIGHT;i++){
        for(int j=0; j<MATRIX_LENGTH;j++){
            (*frame)[i][j] = colorBlank;
        }
    }

}

void DisplayProgram::exit() {

}
