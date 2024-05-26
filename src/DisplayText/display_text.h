//
// Created by leo on 26.05.24.
//

#ifndef TGL_BOARD_DISPLAY_TEXT_DISPLAY_TEXT_H
#define TGL_BOARD_DISPLAY_TEXT_DISPLAY_TEXT_H

class TextController;

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif
#include "display_program.h"






class DisplayText : public DisplayProgram{

    TextController *textController;
    uint8_t currentTextIndex;
    uint8_t currentColorIndex;
    bool newText;
    bool newColor;

    void setText(uint8_t index);
    void setColor(uint8_t index);

public:
    explicit DisplayText(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], TextController* textController);

    void refresh() override;
    void button1ISR(bool state) override;
    void button2ISR(bool state) override;
    void restart() override;



};


#endif //TGL_BOARD_DISPLAY_TEXT_DISPLAY_TEXT_H
