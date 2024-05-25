//
// Created by leo on 25.05.24.
//

#ifndef TGL_BOARD_RAINBOW_ANIMATION_RAINBOW_ANIMATION_H
#define TGL_BOARD_RAINBOW_ANIMATION_RAINBOW_ANIMATION_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif

#include "display_program.h"


namespace details_rainbow_animation{
    extern const uint8_t colorCount;
    extern const Color *rainbowColors[];}


class RainbowAnimation : public DisplayProgram{

    uint8_t currentColor;

    void calcFrame();

public:

    explicit RainbowAnimation(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);


    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;

};


#endif //TGL_BOARD_RAINBOW_ANIMATION_RAINBOW_ANIMATION_H
