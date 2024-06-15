//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_SNAKE_AI_SNAKE_AI_SETTINGS_H
#define TGL_BOARD_SNAKE_AI_SNAKE_AI_SETTINGS_H

namespace details_snake_ai{
    inline const uint8_t LENGTH_GROWTH = 1;
    inline const uint8_t START_LENGTH = 3;

    inline const float AI_MOVES_MAX_SNAKE_SIZE = 0.8;
    inline const uint8_t AI_MOVES_MIN_DISTANCE_TAIL = 1;

    inline const uint8_t LAST_X_PIXELS_DIMMER = MAX_SUBFRAMES-1;





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
