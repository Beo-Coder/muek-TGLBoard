//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SNAKE_AI_SETTINGS_H
#define MUEK_ARGB_MATRIX_BOARD_SNAKE_AI_SETTINGS_H

#include "Arduino.h"

#define LENGTH_GROWTH 1
#define START_LENGTH 1

#define COUNT_GAMES


namespace details_snake_ai{


    enum SnakeDirection{
        None = 0,
        Right = 1,
        Left = 2,
        Up = 4,
        Down = 8
    };

}

#endif //MUEK_ARGB_MATRIX_BOARD_SNAKE_AI_SETTINGS_H
