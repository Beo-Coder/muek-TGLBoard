//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_SETTINGS_H
#define TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_SETTINGS_H


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "PIOMatrixOutput/color.h"

namespace details_dino_game{
    inline const uint32_t FLASH_ACCESS_KEY_HIGH_SCORE = 1;
    inline const uint32_t FLASH_HIGH_SCORE_LENGTH = 4;
    inline uint32_t refreshSeed = 100;
    inline uint32_t scoreRefreshSpeed = 50;



    // Enemy section
    inline const uint8_t MAX_ENEMIES = 2;

    inline const uint8_t ENEMY_BIRD = 0;
    inline const uint8_t ENEMY_WORM = 1;
    inline const uint8_t ENEMY_ENEMY = 2;

    inline const uint8_t ENEMY_SIZE_1 = 0;
    inline const uint8_t ENEMY_SIZE_2 = 1;

    inline const uint8_t ENEMY_TYPES = 6;


    inline const int8_t enemyHeights[ENEMY_TYPES][4] = {{0, 2, ENEMY_ENEMY, ENEMY_SIZE_2},
                                                  {0, 4, ENEMY_WORM,  ENEMY_SIZE_1},
                                                  {3, 2, ENEMY_BIRD,  ENEMY_SIZE_1},
                                                  {6, 1, ENEMY_BIRD,  ENEMY_SIZE_1},
                                                  {5, 1, ENEMY_BIRD,  ENEMY_SIZE_1},
                                                  {4, 1, ENEMY_BIRD,  ENEMY_SIZE_1}
    }; // 0: height; 1: probability; 2: enemySkin; 3: enemySizeIndex;

    inline const int8_t enemySize[3][2] = {
            {3, 2},
            {2, 3},
    };
    // Enemy section END

    // Player section
    inline const uint8_t PLAYER_POS_X = 2;
    inline const uint8_t PLAYER_POS_Y = 0;

    inline const uint8_t PLAYER_SIZE_X = 2;
    inline const uint8_t PLAYER_SIZE_Y = 4;

    inline const uint8_t PLAYER_JUMP_HEIGHT = 3;
    inline const uint8_t PLAYER_JUMP_LENGTH = 9;
    inline const int8_t PLAYER_DUCK_HEIGHT = -1;
    // Player section END

    // Level section
    inline const uint8_t LEVELS = 12;

    inline const uint32_t levels[LEVELS][3] = {
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


    inline const Color *entityColorBlank = &colorBlank;

    inline const Color *playerColor1 = &colorGreen;
    inline const Color *playerColor2 = &colorWhite;


    inline const Color **playerSkin[4][4][2] = {
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



    inline const Color *colorCollision = new Color(3,0,0);


    inline const Color *enemyColor1 = &colorPurple;
    inline const Color *enemyColor2 = &colorRed;
    inline const Color *enemyColor3 = new Color(2,1,0);
    inline const Color *enemyColor4 = &colorBlue;



    inline const Color **enemySkin[10][4][4] = {
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

}

#endif //TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_SETTINGS_H
