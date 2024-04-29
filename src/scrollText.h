//
// Created by leo on 06.03.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SCROLLTEXT_H
#define MUEK_ARGB_MATRIX_BOARD_SCROLLTEXT_H

#include <Arduino.h>
#include "letters.h"
#include "pioMatrixOutput.h"
#include "color.h"
#include "display_program.h"

#define MAX_TEXT_LENGTH 500
#define SPACE_BETWEEN_LETTERS 1




class scrollText : public display_program{


    uint8_t idTextArray[MAX_TEXT_LENGTH];
    uint16_t idTextArraySize;
    uint16_t idTextArrayIndex;

    uint8_t matrixBitOffset;

    Color *textColor;
    Color *backgroundColor;


    void createIDTextArray(String *text);


public:
    explicit scrollText(MatrixOutput *matrixOutput);

    void setText(String *text);
    void setColor(Color *textColor, Color *backgroundColor);

    void shiftText();

    void refresh() override;
    void restart() override;

    void button1ISR(bool state) override;
    void button2ISR(bool state) override;


};


#endif //MUEK_ARGB_MATRIX_BOARD_SCROLLTEXT_H
