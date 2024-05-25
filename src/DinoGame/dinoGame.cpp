//
// Created by leo on 25.04.24.
//

#include "dinoGame.h"
#include "enemy.h"
#include "player.h"
#include "beo_common.h"
#include "TextController/text_controller.h"
#include "FlashController/flash_controller.h"



DinoGame::DinoGame(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], TextController *staticController, FlashController *flashController) : DisplayProgram(ledMatrix, frame) {
    //  matrix = ledMatrix;

    this->flashController = flashController;
    textController = staticController;
    numberEnemies = 1;
    score = 0;

    refreshSpeed = 0;
    dead = false;
    showScore = 0;


    for (details_dino_game::Enemy *&enemy: enemies) {
        enemy = new details_dino_game::Enemy(-1, -1, 0, 0);
    }


    player = new details_dino_game::Player(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_SIZE_X, PLAYER_SIZE_Y);


    createNewEnemy(0);


}

void DinoGame::restart() {

    player->posY = PLAYER_POS_Y;

    numberEnemies = 1;
    score = 0;
    refreshSpeed = 100;
    dead = false;
    showScore = 0;

    for (int i = 1; i < MAX_ENEMIES; i++) {
        enemies[i]->alive = false;
    }

    createNewEnemy(0);

}


void DinoGame::button1ISR(bool data) {
    if (!dead) {
        player->duck(data);
    }

}


void DinoGame::button2ISR(bool data) {
    if(data){
        if (!dead) {
            player->jump();
        } else {
            if(showScore == 0){
                showScore = 1;
            }else if(showScore == 1){
                showScore = 2;
            }else{
                restart();
            }
        }
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
        // If dead, already load score in text controller
        if(dead){
            checkHighScore();


            stringBuffer = "";
            stringBuffer.append(std::to_string(score));

            textController->restart();
            textController->setColor(&colorWhite, &colorBlank);
            textController->setText(&stringBuffer);
            showScore = 0;
        }

    } else {
        switch (showScore){
            case 0:
                // Let the collision pixel blink
                for (int i = 0; i < numberEnemies; i++) {
                    if (player->checkAndMarkCollision(*enemies[i], frame)) {
                        dead = true;
                        refreshSpeed = 250;
                    }
                }
                break;
            case 1:
                // Show score
                textController->createAndLoadFrame();
                break;
            case 2:
                // Load Highscore
                textController->restart();
                textController->setColor(&colorWhite, &colorBlank);
                stringBuffer = "Highest:%2";
                stringBuffer.append(std::to_string(getHighScore()));
                textController->setText(&stringBuffer);
                showScore = 3;
            case 3:
                // Show highScore;
                textController->createAndLoadFrame();
                break;


        }





    }
    matrix->setDisplayData(frame);
    matrix->sendData();


}

uint32_t DinoGame::getHighScore() {
    uint8_t *address = FlashController::readData(details_dino_game::FLASH_ACCESS_KEY_HIGH_SCORE);
    if(address == nullptr){
        return 0;
    }
    uint32_t highScore = 0;
    for(uint32_t i=0; i<details_dino_game::FLASH_HIGH_SCORE_LENGTH; i++){
        highScore |= ((*(address+i)) << (8*i));
    }
    return highScore;
}

void DinoGame::storeNewHighScore() {
    uint8_t data[4];
    for(uint32_t i=0; i<details_dino_game::FLASH_HIGH_SCORE_LENGTH; i++){
        data[i] = (score >> (8*i)) &0xFF;
    }
    flashController->writeData(details_dino_game::FLASH_ACCESS_KEY_HIGH_SCORE, data);

}

void DinoGame::checkHighScore() {
    if(score > getHighScore()){
        storeNewHighScore();
    }
}











