//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_SETTINGS_H
#define TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_SETTINGS_H


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "PIOMatrixOutput/color.h"


// Enemy section
#define MAX_ENEMIES 2

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
}; // 0: height; 1: probability; 2: enemySkin; 3: enemySizeIndex;

static int8_t enemySize[3][2] = {
        {3, 2},
        {2, 3},
};
// Enemy section END

// Player section
#define PLAYER_POS_X 2
#define PLAYER_POS_Y 0

#define PLAYER_SIZE_X 2
#define PLAYER_SIZE_Y 4

#define PLAYER_JUMP_HEIGHT 3
#define PLAYER_JUMP_LENGTH 9
#define PLAYER_DUCK_HEIGHT (-1)
// Player section END

// Level section
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

// Level section END


static Color *entityColorBlank = &colorBlank;

static Color *playerColor1 = &colorGreen;
static Color *playerColor2 = &colorWhite;


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

/*
static Color colorEnemyDarkRed(3,0,0);
static Color colorEnemyOrange;
static Color colorEnemyBlue;
 */

static Color *colorCollision = new Color(3,0,0);


static Color *enemyColor1 = &colorPurple;
static Color *enemyColor2 = &colorRed;
static Color *enemyColor3 = new Color(2,1,0);
static Color *enemyColor4 = &colorBlue;



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
                {&enemyColor2, &enemyColor4},
                {&enemyColor4,      &entityColorBlank},
        },
        {

                {&enemyColor4,      &enemyColor4},
                {&enemyColor2, &enemyColor4},
                {&entityColorBlank, &enemyColor4},

        }
};



#endif //TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_SETTINGS_H
