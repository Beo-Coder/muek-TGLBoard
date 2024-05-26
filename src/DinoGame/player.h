//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_FIREWORK_DINO_GAME_PLAYER_H
#define TGL_BOARD_FIREWORK_DINO_GAME_PLAYER_H
namespace details_dino_game {
    class Enemy;
}
class Color;


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "PIOMatrixOutput/pio_matrix_settings.h"
#include "entity.h"



namespace details_dino_game {
    class Player : public Entity {
        int32_t lastJump;


    public:

        Player(int8_t startPosX, int8_t startPosY, int8_t sizeX, int8_t sizeY);

        void jump();

        void duck(bool pressed);

        void checkJumped();

        void animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) override;

        bool checkAndMarkCollision(const Enemy &entity, Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);

        void reset();

    };
}


#endif //TGL_BOARD_FIREWORK_DINO_GAME_PLAYER_H
