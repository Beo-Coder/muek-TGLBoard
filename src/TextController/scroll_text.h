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



class ScrollText : public TextController{



    bool leftShift;


protected:
    inline static uint8_t spaceBetweenLetters = 1;

    uint8_t matrixBitOffset;
    void createIDTextArray(String *text) override;


    void shiftToLeftSide();

    void shiftTextLeft();
    void shiftTextRight();

    void loadNewBitsLeftShift();
    void loadNewBitsRightShift();






public:
    explicit ScrollText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void setMode(bool leftShift = true);
    void setSpaceBetweenLetters(uint8_t space);

    virtual void createAndLoadFrame();



    void refresh() override;
    void restart() override;



};


#endif //MUEK_ARGB_MATRIX_BOARD_SCROLL_TEXT_H
