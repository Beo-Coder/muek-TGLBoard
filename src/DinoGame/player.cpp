//
// Created by leo on 01.05.24.
//

#include "player.h"
#include "enemy.h"
#include "dinogame_settings.h"

details_dino_game::Player::Player(int8_t startPosX, int8_t startPosY, int8_t sizeX, int8_t sizeY) : Entity(startPosX,
                                                                                                           startPosY,
                                                                                                           sizeX,
                                                                                                           sizeY) {
    lastJump = 0;
}

void details_dino_game::Player::jump() {
    if (lastJump - PLAYER_JUMP_LENGTH > 0 && posY != PLAYER_DUCK_HEIGHT) {
        posY = PLAYER_JUMP_HEIGHT;
        lastJump = 0;
    }
}

void details_dino_game::Player::duck(bool pressed) {
    if (pressed) {
        posY = PLAYER_DUCK_HEIGHT;
        lastJump = PLAYER_JUMP_LENGTH;
    } else {
        posY = PLAYER_POS_Y;
        lastJump = PLAYER_JUMP_LENGTH;
    }


}

void details_dino_game::Player::checkJumped() {
    if (lastJump - PLAYER_JUMP_LENGTH >= 0 && posY != PLAYER_DUCK_HEIGHT) {
        posY = PLAYER_POS_Y;
    }
    lastJump++;
}


void details_dino_game::Player::animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {

    skinIndex = (skinIndex + 1) % 2;
    if (posY == PLAYER_DUCK_HEIGHT) {
        skinIndex = skinIndex + 2;
    }


    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            if (posX + j < MATRIX_LENGTH && posX + j >= 0 && posY + i < MATRIX_HEIGHT && posY + i >= 0) {
                (*display)[MATRIX_HEIGHT - (posY + i) - 1][posX + j] = *(*playerSkin[skinIndex][sizeY - i - 1][j]);
            }
        }
    }
}

bool
details_dino_game::Player::checkAndMarkCollision(const Enemy &entity, Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    bool returnData = false;
    for (int8_t py = posY; py < posY + sizeY; py++) {
        for (int8_t px = posX; px < posX + sizeX; px++) {
            for (int8_t ey = entity.posY; ey < entity.posY + entity.sizeY; ey++) {
                for (int8_t ex = entity.posX; ex < entity.posX + entity.sizeX; ex++) {
                    if (py == ey && px == ex) {
                        if (((*display)[MATRIX_HEIGHT - (py) - 1][px]).calc() == colorCollision->calc()) {
                            (*display)[MATRIX_HEIGHT - (py) - 1][px] = *entityColorBlank;
                        } else {
                            (*display)[MATRIX_HEIGHT - (py) - 1][px] = *colorCollision;
                        }

                        returnData = true;
                    }

                }
            }
        }

    }
    return returnData;

}

void details_dino_game::Player::reset() {
    lastJump = PLAYER_JUMP_LENGTH;
    skinIndex = 0;
    posY = PLAYER_POS_Y;


}
