//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_FIREWORK_DINO_GAME_ENEMY_H
#define TGL_BOARD_FIREWORK_DINO_GAME_ENEMY_H


class Color;


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "entity.h"
#include "PIOMatrixOutput/pio_matrix_settings.h"





namespace details_dino_game {
    class Enemy : public Entity {
    public:

        Enemy(int8_t startPosX, int8_t startPosY, int8_t sizeX, int8_t sizeY);

        Enemy();

        uint8_t enemyType;
        bool alive;


        void animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) override;

        void move();


    };
}


#endif //TGL_BOARD_FIREWORK_DINO_GAME_ENEMY_H
