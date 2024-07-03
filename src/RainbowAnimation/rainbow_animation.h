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



enum RainbowMode{fixed = 0, smooth = 1};


namespace details_rainbow_animation{

    inline const uint32_t REFRESH_SPEED = 120;
    inline const float BRIGHTNESS_FACTOR = 2.0;



    inline const uint8_t colorCount = 6;
    inline const Color *rainbowColors[] = {&colorPurple, &colorBlue,&colorCyan, &colorGreen, &colorYellow, &colorRed};

}


class RainbowAnimation : public DisplayProgram{

    Color pixelColor;

    uint8_t currentColor;

    RainbowMode mode;
    uint8_t numberColorValues;

    void calcFrame();

public:

    explicit RainbowAnimation(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);


    void setMode(RainbowMode mode);

    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;

};


#endif //TGL_BOARD_RAINBOW_ANIMATION_RAINBOW_ANIMATION_H
