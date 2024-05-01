//
// Created by leo on 01.05.24.
//

#include "enemy.h"
details_dino_game::Enemy::Enemy(int8_t startPosX, int8_t startPosY, int8_t sizeX, int8_t sizeY) : Entity(startPosX,
                                                                                                        startPosY,
                                                                                                        sizeX, sizeY) {
    alive = false;
    enemyType = 0;
}

details_dino_game::Enemy::Enemy() : Entity() {
    alive = false;
    enemyType = 0;
}


void details_dino_game::Enemy::animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    if (alive) {
        uint8_t localSkinIndex;
        switch (enemyType) {
            case ENEMY_BIRD:
                skinIndex = (skinIndex + 1) % 4;
                localSkinIndex = skinIndex / 2;
                break;
            case ENEMY_WORM:
                skinIndex = (skinIndex + 1) % 6;
                localSkinIndex = (skinIndex / 3) + 2;
                break;
            case ENEMY_ENEMY:
                skinIndex = (skinIndex + 1) % 2;
                localSkinIndex = (skinIndex) + 4;
                break;
        }


        for (int8_t i = 0; i < sizeY; i++) {
            for (int8_t j = 0; j < sizeX; j++) {
                if (posX + j < MATRIX_LENGTH && posX + j >= 0 && posY + i < MATRIX_HEIGHT && posY + i >= 0) {
                    (*display)[MATRIX_HEIGHT - (posY + i) - 1][posX + j] = *(*enemySkin[localSkinIndex][sizeY - i -
                                                                                                        1][j]);
                }
            }
        }
    }
}

void details_dino_game::Enemy::move() {
    if (posX + sizeX <= 0) {
        alive = false;
    } else {
        posX--;
    }

}
