//
// Created by leo on 06.03.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SCROLLTEXT_H
#define MUEK_ARGB_MATRIX_BOARD_SCROLLTEXT_H

#include <Arduino.h>
#include "letters.h"
#include "pioMatrixOutput.h"
#include "color.h"

#define MAX_TEXT_LENGTH 500
#define SPACE_BETWEEN_LETTERS 1




class scrollText {

    MatrixOutput *displayController;

    uint8_t idTextArray[MAX_TEXT_LENGTH];
    uint16_t idTextArraySize;
    uint16_t idTextArrayIndex;

    uint8_t matrixBitOffset;

    Color *textColor;
    Color *backgroundColor;

    Color displayData[MATRIX_HEIGHT][MATRIX_LENGTH];

    void createIDTextArray(String *text);


public:
    scrollText(MatrixOutput *displayController);

    void setText(String *text);
    void setColor(Color *textColor, Color *backgroundColor);

    void shiftText();


};


#endif //MUEK_ARGB_MATRIX_BOARD_SCROLLTEXT_H
