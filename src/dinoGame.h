//
// Created by leo on 25.04.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_DINOGAME_H
#define MUEK_ARGB_MATRIX_BOARD_DINOGAME_H

#include "Arduino.h"
#include "pioMatrixOutput.h"
#include "color.h"


#define JUMP_HEIGHT 3
#define JUMP_LENGTH 9
#define DUCK_HEIGHT (-1)


#define ENEMY_BIRD 0
#define ENEMY_WORM 1
#define ENEMY_ENEMY 2

#define ENEMY_SIZE_1 0
#define ENEMY_SIZE_2 1

#define ENEMY_TYPES 6


static int8_t enemyHeights[ENEMY_TYPES][4] = {{0, 2, ENEMY_ENEMY, ENEMY_SIZE_2},
                                              {0, 4, ENEMY_WORM,  ENEMY_SIZE_1},
                                              {3, 2, ENEMY_BIRD,  ENEMY_SIZE_1},
                                              {6, 1, ENEMY_BIRD,  ENEMY_SIZE_1},
                                              {5, 1, ENEMY_BIRD,  ENEMY_SIZE_1},
                                              {4, 1, ENEMY_BIRD,  ENEMY_SIZE_1}
}; //0: height; 1: probability; 2: enemySkin; 3: enemySizeIndex;

static int8_t enemySize[3][2] = {
        {3, 2},
        {2, 3},
};


#define LEVELS 12

static uint32_t levels[LEVELS][3] = {
        {0,    100, 1},
        {100,  100, 2},
        {500,  95,  2},
        {1000, 90,  2},
        {1300, 85,  2},
        {1600, 80,  2},
        {1900, 75,  2},
        {2100, 70,  2},
        {2300, 65,  2},
        {2500, 60,  2},
        {2700, 55,  2},
        {3000, 50,  2}}; // score, speed, enemies







static Color colorDarkRed;
static Color colorRed;
static Color colorGrey;
static Color colorGreen;
static Color colorBlank;

static Color colorEnemyDarkRed;
static Color colorEnemyYellow;
static Color colorEnemyOrange;
static Color colorEnemyBlue;

static Color *entityColorBlank;

static Color *playerColor1;
static Color *playerColor2;
static Color *playerColor3;


static Color **playerSkin[4][4][2] = {
        {
                {&playerColor1, &playerColor1},
                {&playerColor1, &playerColor2},
                {&playerColor1,     &playerColor1},
                {&playerColor1,     &entityColorBlank},
        },
        {
                {&playerColor1, &playerColor1},
                {&playerColor1, &playerColor2},
                {&playerColor1,     &playerColor1},
                {&entityColorBlank, &playerColor1},
        },
        {
                {&playerColor1, &playerColor1},
                {&playerColor1, &playerColor2},
                {&playerColor1,     &entityColorBlank},
        },
        {
                {&playerColor1, &playerColor1},
                {&playerColor1, &playerColor2},
                {&entityColorBlank, &playerColor1},
        }
};


static Color *enemyColor1;
static Color *enemyColor2;
static Color *enemyColor3;
static Color *enemyColor4;
static Color *enemyColor5;


static Color **enemySkin[10][4][4] = {
        {
                {&entityColorBlank, &enemyColor1,      &entityColorBlank},
                {&enemyColor2, &enemyColor1,      &enemyColor1},
        },
        {
                {&entityColorBlank, &entityColorBlank, &entityColorBlank},
                {&enemyColor2, &enemyColor1,      &enemyColor1},
        },
        {
                {&entityColorBlank, &enemyColor3,      &entityColorBlank},
                {&enemyColor3, &entityColorBlank, &enemyColor3},
        },
        {
                {&entityColorBlank, &entityColorBlank, &entityColorBlank},
                {&enemyColor3, &enemyColor3,      &enemyColor3},
        },
        {
                {&enemyColor4,      &enemyColor4},
                {&enemyColor5, &enemyColor4},
                {&enemyColor4,      &entityColorBlank},
        },
        {

                {&enemyColor4,      &enemyColor4},
                {&enemyColor5, &enemyColor4},
                {&entityColorBlank, &enemyColor4},

        }
};


class Entity {
public:
    int8_t posX = 16;
    int8_t posY;
    int8_t sizeX;
    int8_t sizeY;
    uint8_t skinIndex = 0;
    uint8_t entityType;

    bool alive;

    void move();

    virtual void animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);


};

class Player : public Entity {
    int32_t lastJump = 0;


public:

    void jump();

    void duck(bool pressed);

    void animate(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) override;

    bool checkAndMarkCollision(Entity entity, Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);

};

class DinoGame {

    Color frame[MATRIX_HEIGHT][MATRIX_LENGTH];

    Entity enemies[2];
    uint8_t numberEnemies;
    Player player;


    MatrixOutput *matrix;
    bool dead = false;

    void animateFrame();

    void moveEntities();

    void createNewEnemy(uint8_t index);


public:
    uint32_t score;
    uint8_t speed;

    DinoGame(MatrixOutput *ledMatrix);


    void button1ISR(bool data);

    void button2ISR();

    void refresh();

    void restart();


};


#endif //MUEK_ARGB_MATRIX_BOARD_DINOGAME_H
