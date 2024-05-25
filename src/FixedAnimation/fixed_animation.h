//
// Created by leo on 25.05.24.
//

#ifndef TGL_BOARD_FIXED_ANIMATION_FIXED_ANIMATION_H
#define TGL_BOARD_FIXED_ANIMATION_FIXED_ANIMATION_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif



#include "display_program.h"
#include "animations/animations.h"


class FixedAnimation : public DisplayProgram{

    uint16_t frameIndex;
    uint8_t animationIndex;
    const Animation *currenAnimation;


public:

    explicit FixedAnimation(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);


    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;

};


#endif //TGL_BOARD_FIXED_ANIMATION_FIXED_ANIMATION_H
