//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_FIREWORK_H
#define MUEK_ARGB_MATRIX_BOARD_FIREWORK_H


#include "pico/stdlib.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "PIOMatrixOutput/color.h"
#include "BeoCommon.h"

#include "firework_settings.h"
#include "pixel.h"


namespace details_firework {
    class Firework {

        Pixel *pixel[PIXEL_PER_FIREWORK];
        Color pixelColor;

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
    };

};



#endif //MUEK_ARGB_MATRIX_BOARD_FIREWORK_H
