//
// Created by leo on 25.04.24.
//

#include "dinoGame.h"


void Entity::animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    if (alive) {
        uint8_t localSkinIndex;
        switch(entityType){
            case ENEMY_BIRD:
                skinIndex = (skinIndex + 1) % 4;
                localSkinIndex = skinIndex /2;
                break;
            case ENEMY_WORM:
                skinIndex = (skinIndex + 1) % 6;
                localSkinIndex = (skinIndex /3) + 2;
                break;
            case ENEMY_ENEMY:
                skinIndex = (skinIndex + 1) % 2;
                localSkinIndex = (skinIndex) + 4;
                break;


        }


        for (int8_t i = 0; i < sizeY; i++) {
            for (int8_t j = 0; j < sizeX; j++) {
                if (posX + j < MATRIX_LENGTH && posX + j >= 0 && posY + i < MATRIX_HEIGHT && posY + i >= 0) {
                    (*display)[MATRIX_HEIGHT - (posY + i) - 1][posX + j] = *(*enemySkin[localSkinIndex][sizeY-i-1][j]);
                }
            }
        }
    }
}

void Entity::move() {
    if (posX + sizeX == 0) {
        alive = false;
    } else {
        posX--;
    }

}

void Player::jump() {
    if (lastJump - JUMP_LENGTH > 0 && posY != DUCK_HEIGHT) {
        posY = JUMP_HEIGHT;
        lastJump = 0;
    }
}

void Player::duck(bool pressed) {
    if(pressed){
        posY = DUCK_HEIGHT;
        lastJump = JUMP_LENGTH;
    }else{
        posY = 0;
        lastJump = JUMP_LENGTH;
    }


}

void Player::animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    if (lastJump - JUMP_LENGTH >= 0 && posY != DUCK_HEIGHT) {
        posY = 0;
    }


    lastJump++;


    skinIndex = (skinIndex + 1) %2;
    if(posY == DUCK_HEIGHT){
        skinIndex = skinIndex+2;
    }


    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            if (posX + j < MATRIX_LENGTH && posX + j >= 0 && posY + i < MATRIX_HEIGHT && posY + i >= 0) {
                (*display)[MATRIX_HEIGHT - (posY + i) - 1][posX + j] = *(*playerSkin[skinIndex][sizeY-i-1][j]);
            }
        }
    }
}

bool Player::checkAndMarkCollision(const Entity& entity, Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    bool returnData = false;
    for (int8_t py = posY; py < posY + sizeY; py++) {
        for (int8_t px = posX; px < posX + sizeX; px++) {
            for (int8_t ey = entity.posY; ey < entity.posY + entity.sizeY; ey++) {
                for (int8_t ex = entity.posX; ex < entity.posX + entity.sizeX; ex++) {
                    if (py == ey && px == ex) {
                        if(((*display)[MATRIX_HEIGHT - (py) - 1][px]).calc() ==  colorDarkRed.calc()){
                            (*display)[MATRIX_HEIGHT - (py) - 1][px] = colorBlank;
                        }else{
                            (*display)[MATRIX_HEIGHT - (py) - 1][px] = colorDarkRed;
                        }

                        returnData = true;
                    }

                }
            }
        }

    }
    return returnData;

}


DinoGame::DinoGame(MatrixOutput *ledMatrix) {
    matrix = ledMatrix;



    player.posX = 2;
    player.posY = 0;
    player.sizeX = 2;
    player.sizeY = 4;


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

    restart();






}

void DinoGame::restart() {

    player.posY = 0;



    numberEnemies = 1;
    score = 0;
    speed = 100;
    dead = false;

    enemies[1].alive = false;

    createNewEnemy(0);




}


void DinoGame::button1ISR(bool data) {
    if (!dead) {
        player.duck(data);
        animateFrame();
    }

}





void DinoGame::button2ISR() {
    if (!dead) {
        player.jump();
    } else {
        restart();
    }
    animateFrame();


}


int8_t* getRandomEnemy() {


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


    int8_t* enemy = getRandomEnemy();

    enemies[index].posY = enemy[0];
    enemies[index].entityType = enemy[2];

    enemies[index].sizeX = enemySize[enemy[3]][0];
    enemies[index].sizeY = enemySize[enemy[3]][1];

    //enemies[index].posX = 16;
    enemies[index].posX = 16 + enemies[numberEnemies - 1 - index].sizeX - (rand() % 1) + (rand() % 1);
    enemies[index].alive = true;


}

void DinoGame::animateFrame() {
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_LENGTH; j++) {
            frame[i][j] = colorBlank;
        }
    }

    for (int i = 0; i < numberEnemies; i++) {
        enemies[i].animate(&frame);
    }

    player.animate(&frame);

    //matrix->setDisplayData(&frame);
    //matrix->sendData();

}

void DinoGame::moveEntities() {
    for (int i = 0; i < numberEnemies; i++) {
        enemies[i].move();
    }
}

void DinoGame::refresh() {
    if (!dead) {
        score++;

        moveEntities();
        animateFrame();

        for(int i=0;i<LEVELS;i++){
            if(score > levels[i][0]){
                speed = levels[i][1];
                if(numberEnemies < levels[i][2]){
                    if(enemies[numberEnemies-1].posX == 15){
                        createNewEnemy(numberEnemies);
                        enemies[numberEnemies].posX = enemies[numberEnemies-1].posX + enemies[numberEnemies-1].sizeX + 8;

                        numberEnemies++;
                    }

                }
            }
        }



        for (int i = 0; i < numberEnemies; i++) {
            if (!enemies[i].alive) {
                createNewEnemy(i);
            }
            if (player.checkAndMarkCollision(enemies[i], &frame)) {
                dead = true;
                speed = 250;
            }



        }

    }else{
        for (int i = 0; i < numberEnemies; i++) {
            if (player.checkAndMarkCollision(enemies[i], &frame)) {
                dead = true;
                speed = 250;
            }
        }
    }
    matrix->setDisplayData(&frame);
    matrix->sendData();


}









