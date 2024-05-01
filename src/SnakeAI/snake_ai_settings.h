//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SNAKE_AI_SETTINGS_H
#define MUEK_ARGB_MATRIX_BOARD_SNAKE_AI_SETTINGS_H

#define LENGTH_GROWTH 1
#define START_LENGTH 1

#include "Arduino.h"

namespace details_snake_ai{

    struct Position{
        int16_t posX;
        int16_t posY;
        int8_t directionX;
        int8_t directionY;
    } ;


    enum SnakeDirection{
        None = 0,
        Right = 1,
        Left = 2,
        Up = 4,
        Down = 8
    };

}

#endif //MUEK_ARGB_MATRIX_BOARD_SNAKE_AI_SETTINGS_H
