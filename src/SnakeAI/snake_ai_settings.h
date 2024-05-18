//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_SNAKE_AI_SNAKE_AI_SETTINGS_H
#define TGL_BOARD_SNAKE_AI_SNAKE_AI_SETTINGS_H


#define LENGTH_GROWTH 1
#define START_LENGTH 3

#define AI_MOVES_MAX_SNAKE_SIZE (0.9)
#define AI_MOVES_MIN_DISTANCE_TAIL 1


// !!!!!DO NOT CHANGE!!!!!
namespace details_snake_ai{

    // !!!!!DO NOT CHANGE!!!!!
    enum Direction{
        None = 0,
        Right = 1,
        Left = -1,
        Up = (1<<8),
        Down = -(1<<8)
    };

}

#endif //TGL_BOARD_SNAKE_AI_SNAKE_AI_SETTINGS_H
