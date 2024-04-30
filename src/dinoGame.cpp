//
// Created by leo on 25.04.24.
//

#include "dinoGame.h"


details_dino_game::Entity::Entity(int8_t startPosX, int8_t startPosY, int8_t sizeX, int8_t sizeY) {
    posX = startPosX;
    posY = startPosY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;

}

details_dino_game::Entity::Entity() {
    posX = -1;
    posY = -1;
    sizeX = 0;
    sizeY = 0;
}


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








DinoGame::DinoGame(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) : display_program(ledMatrix, frame) {
    //  matrix = ledMatrix;

    numberEnemies = 1;
    score = 0;

    refreshSpeed = 0;
    dead = false;


    for (details_dino_game::Enemy *&enemy: enemies) {
        enemy = new details_dino_game::Enemy(-1, -1, 0, 0);
    }


    player = new details_dino_game::Player(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_SIZE_X, PLAYER_SIZE_Y);


    createNewEnemy(0);


    // Color shit
/*
    colorDarkRed.red = 3;
    colorRed.red = 1;

    colorGrey.red = 1;
    colorGrey.green = 1;
    colorGrey.blue = 1;

    colorGreen.green = 1;

    playerColor1 = &colorGreen;
    playerColor2 = &colorGrey;
    playerColor3 = &colorBlank;
    entityColorBlank = &colorBlank;


    colorEnemyDarkRed.red = 2;
    colorEnemyDarkRed.blue = 2;

    colorEnemyOrange.red = 2;
    colorEnemyOrange.green = 1;

    enemyColor1 = &colorEnemyDarkRed;
    enemyColor2 = &colorRed;

    enemyColor3 = &colorEnemyOrange;

    colorEnemyBlue.blue = 2;
    enemyColor4 = &colorEnemyBlue;

    enemyColor5 = &colorRed;
    */



}

void DinoGame::restart() {

    player->posY = PLAYER_POS_Y;

    numberEnemies = 1;
    score = 0;
    refreshSpeed = 100;
    dead = false;

    for (int i = 1; i < MAX_ENEMIES; i++) {
        enemies[i]->alive = false;
    }

    createNewEnemy(0);

}


void DinoGame::button1ISR(bool data) {
    if (!dead) {
        player->duck(data);
        // animateFrame();
    }

}


void DinoGame::button2ISR(bool data) {
    if(data){
        if (!dead) {
            player->jump();
        } else {
            restart();
        }
        // animateFrame();
    }

}


int8_t *getRandomEnemy() {


    unsigned int totalWeight = 0;
    for (int i = 0; i < ENEMY_TYPES; i++) {
        totalWeight += enemyHeights[i][1];
    }

    unsigned int randomValue = rand() % totalWeight;


    unsigned int cumulativeWeight = 0;
    for (int i = 0; i < ENEMY_TYPES; i++) {
        cumulativeWeight += enemyHeights[i][1];
        if (randomValue < cumulativeWeight) {
            return enemyHeights[i];
        }
    }
    return nullptr;


}


void DinoGame::createNewEnemy(uint8_t index) {

    int8_t *enemy = getRandomEnemy();

    enemies[index]->posY = enemy[0];
    enemies[index]->enemyType = enemy[2];

    enemies[index]->sizeX = enemySize[enemy[3]][0];
    enemies[index]->sizeY = enemySize[enemy[3]][1];


    enemies[index]->posX = MATRIX_LENGTH + enemies[numberEnemies - 1 - index]->sizeX; // For more randomness (could make the levels impossible): - (randomInt(0,2)) + (randomInt(0,2));
    enemies[index]->alive = true;


}

void DinoGame::animateFrame() {
    clearFrame();

    for (int i = 0; i < numberEnemies; i++) {
        enemies[i]->animate(frame);
    }
    player->checkJumped();
    player->animate(frame);


}

void DinoGame::moveEntities() {
    for (int i = 0; i < numberEnemies; i++) {
        enemies[i]->move();
    }
}

void DinoGame::checkScore() {
    for (int i = 0; i < LEVELS; i++) {
        if (score > levels[i][0]) {
            refreshSpeed = levels[i][1];
            if (numberEnemies < levels[i][2]) {
                if (enemies[numberEnemies - 1]->posX == 15) {
                    createNewEnemy(numberEnemies);
                    enemies[numberEnemies]->posX =
                            enemies[numberEnemies - 1]->posX + enemies[numberEnemies - 1]->sizeX + 8;

                    numberEnemies++;
                }

            }
        }
    }

}

void DinoGame::refresh() {
    if (!dead) {
        score++;

        moveEntities();
        animateFrame();
        checkScore();



        for (int i = 0; i < numberEnemies; i++) {
            // Create a new enemy if one is dead
            if (!enemies[i]->alive) {
                createNewEnemy(i);
            }
            // Check for collision between player and enemy
            if (player->checkAndMarkCollision(*enemies[i], frame)) {
                dead = true;
                refreshSpeed = 250;
            }
        }

    } else {
        // Let the collision pixel blink
        for (int i = 0; i < numberEnemies; i++) {
            if (player->checkAndMarkCollision(*enemies[i], frame)) {
                dead = true;
                refreshSpeed = 250;
            }
        }
    }
    matrix->setDisplayData(frame);
    matrix->sendData();


}











