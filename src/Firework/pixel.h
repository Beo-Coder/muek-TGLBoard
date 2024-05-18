//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_FIREWORK_PIXEL_H
#define TGL_BOARD_FIREWORK_PIXEL_H

class Color;

#include <Arduino.h>



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


#endif //TGL_BOARD_FIREWORK_PIXEL_H
