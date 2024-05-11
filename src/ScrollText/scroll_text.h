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

#define MAX_TEXT_LENGTH 500
#define SPACE_BETWEEN_LETTERS 1

#define NUMBER_FREE_PIXELS_ADDED_STATIC_TEXT 3 // Note that SPACE_BETWEEN LETTERS is also added. Only added if text is to large to fit on display
#define STATIC_TEXT_WAIT_TIME_START 3
#define STATIC_TEXT_WAIT_TIME_END 3


class ScrollText : public display_program{


    uint8_t idTextArray[MAX_TEXT_LENGTH];
    uint16_t idTextArraySize;
    uint16_t idTextArrayIndex;

    uint8_t matrixBitOffset;

    Color *textColor;
    Color *backgroundColor;

    bool scroll;
    bool needScrolling;


    uint8_t staticTextTime;
    bool stopScrolling;

    void createIDTextArray(String *text);

    void shiftText();

    void setStaticText();
    void shiftToLeftSide();
    void staticText();





public:
    explicit ScrollText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void setText(String *text, bool scroll = true);
    void setColor(Color *textColor, Color *backgroundColor);



    void refresh() override;
    void restart() override;

    void button1ISR(bool state) override;
    void button2ISR(bool state) override;


};


#endif //MUEK_ARGB_MATRIX_BOARD_SCROLL_TEXT_H
