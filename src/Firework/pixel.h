//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_PIXEL_H
#define MUEK_ARGB_MATRIX_BOARD_PIXEL_H

#include "pico/stdlib.h"
#include "PIOMatrixOutput/color.h"


namespace details_firework {
    class Pixel {

    public:
        Pixel();

        float posX;
        float posY;

        float dirX;
        float dirY;

        Color *color;
    };
}


#endif //MUEK_ARGB_MATRIX_BOARD_PIXEL_H
