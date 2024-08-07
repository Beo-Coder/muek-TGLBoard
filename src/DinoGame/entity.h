//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_FIREWORK_DINO_GAME_ENTITY_H
#define TGL_BOARD_FIREWORK_DINO_GAME_ENTITY_H

class Color;


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "PIOMatrixOutput/pio_matrix_settings.h"



namespace details_dino_game {
    class Entity {
    public:
        int8_t posX;
        int8_t posY;
        int8_t sizeX;
        int8_t sizeY;

        uint8_t skinIndex = 0;


        Entity(int8_t startPosX, int8_t startPosY, int8_t sizeX, int8_t sizeY);
        Entity();


        virtual void animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) = 0;


    };
}



#endif //TGL_BOARD_FIREWORK_DINO_GAME_ENTITY_H
