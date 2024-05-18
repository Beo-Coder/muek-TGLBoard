//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_ENEMY_H
#define MUEK_ARGB_MATRIX_BOARD_ENEMY_H


class Color;

#include <Arduino.h>
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


#endif //MUEK_ARGB_MATRIX_BOARD_ENEMY_H
