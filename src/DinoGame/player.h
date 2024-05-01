//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_PLAYER_H
#define MUEK_ARGB_MATRIX_BOARD_PLAYER_H

#include "Arduino.h"
#include "color.h"

#include "dinogame_settings.h"
#include "entity.h"
#include "enemy.h"



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

    };
}


#endif //MUEK_ARGB_MATRIX_BOARD_PLAYER_H
