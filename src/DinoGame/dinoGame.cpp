//
// Created by leo on 25.04.24.
//

#include "dinoGame.h"
#include "enemy.h"
#include "player.h"
#include "beo_common.h"


















DinoGame::DinoGame(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) : DisplayProgram(ledMatrix, frame) {
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


const int8_t *getRandomEnemy() {


    unsigned int totalWeight = 0;
    for (int i = 0; i < ENEMY_TYPES; i++) {
        totalWeight += enemyHeights[i][1];
    }

    unsigned int randomValue = beo::randomInt(0, totalWeight);


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

    const int8_t *enemy = getRandomEnemy();

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











