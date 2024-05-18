//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_FIREWORK_PIXEL_H
#define TGL_BOARD_FIREWORK_PIXEL_H

class Color;

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif


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
