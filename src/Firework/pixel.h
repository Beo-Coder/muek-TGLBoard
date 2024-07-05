//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_FIREWORK_PIXEL_H
#define TGL_BOARD_FIREWORK_PIXEL_H


#ifdef ARDUINO
    #include <Arduino.h>


#else
    #include "pico/stdlib.h"
#endif
#include "PIOMatrixOutput/color.h"

namespace details_firework {
    class Pixel {

    public:
        Pixel();

        float posX;
        float posY;

        int8_t dirX;
        int8_t dirY;

        Color screenColor;
    };
}


#endif //TGL_BOARD_FIREWORK_PIXEL_H
