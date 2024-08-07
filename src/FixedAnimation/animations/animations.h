//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_FIXED_ANIMATION_ANIMATION_ANIMATIONS_H
#define TGL_BOARD_FIXED_ANIMATION_ANIMATION_ANIMATIONS_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif
#include "PIOMatrixOutput/pio_matrix_output.h"


struct Animation{
    const Color** colorIndex;
    const uint8_t length;
    const uint8_t speed;
    const uint8_t ((**frames[])[MATRIX_HEIGHT][MATRIX_LENGTH]);
};

// Jump animation
extern const uint8_t (*jumpAnimationFrames[])[MATRIX_HEIGHT][MATRIX_LENGTH];
extern const Color* jumpAnimationColorIndex[];

inline const Animation jumpAnimation{jumpAnimationColorIndex,45,150,{jumpAnimationFrames}};




// All animations
inline const Animation *animations[] = {&jumpAnimation};








#endif //TGL_BOARD_FIXED_ANIMATION_ANIMATION_ANIMATIONS_H
