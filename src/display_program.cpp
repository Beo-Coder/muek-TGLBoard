//
// Created by leo on 29.04.24.
//
#include "display_program.h"

display_program::display_program(MatrixOutput *matrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    this->matrix = matrix;
    this->frame = frame;
}

void display_program::clearFrame() {
    for(int i=0; i<MATRIX_HEIGHT;i++){
        for(int j=0; j<MATRIX_LENGTH;j++){
            (*frame)[i][j] = colorBlank;
        }
    }

}
