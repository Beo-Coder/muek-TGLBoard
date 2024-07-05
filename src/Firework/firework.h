//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_FIREWORK_FIREWORK_H
#define TGL_BOARD_FIREWORK_FIREWORK_H


namespace details_firework {
    class Pixel;
}
class Color;


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "PIOMatrixOutput/pio_matrix_settings.h"
#include "firework_settings.h"
#include "pixel.h"


namespace details_firework {
    class Firework {

        Pixel pixel[PIXEL_PER_FIREWORK];
        Color pixelColor;

        uint8_t explosionBrightness;

        int8_t startPosX;
        int8_t startPosY;

        uint8_t lifeTime;
        bool arrived;
        bool exploded;


        void calcFireworkTrail(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);

        void calcFireworkExplosion(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);


    public:
        Firework();

        bool dead;

        void start(int8_t posX, int8_t posY, Color *color);

        void calcFrame(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);
        void reset();
    };

};



#endif //TGL_BOARD_FIREWORK_FIREWORK_H
