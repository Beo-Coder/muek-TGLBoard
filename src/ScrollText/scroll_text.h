//
// Created by leo on 06.03.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SCROLL_TEXT_H
#define MUEK_ARGB_MATRIX_BOARD_SCROLL_TEXT_H

#include <Arduino.h>
#include "letters.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "color.h"
#include "display_program.h"
#include "text_controller.h"

#define MAX_TEXT_LENGTH 500
#define SPACE_BETWEEN_LETTERS 1



class ScrollText : public TextController{


    uint8_t matrixBitOffset;


protected:
    void createIDTextArray(String *text) override;
    void shiftText();
    void shiftToLeftSide();




public:
    explicit ScrollText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);



    void refresh() override;
    void restart() override;



};


#endif //MUEK_ARGB_MATRIX_BOARD_SCROLL_TEXT_H
