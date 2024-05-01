//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SNAKE_H
#define MUEK_ARGB_MATRIX_BOARD_SNAKE_H

#include "Arduino.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "BeoCommon.h"

#include "snake_ai_settings.h"

namespace details_snake_ai {
    class Snake {
        boolean dead;

        int16_t length;


    public:
        Position snakeBody[MATRIX_SIZE];

        Snake();

        void setPosition(int16_t posX, int16_t posY);

        Position getPosition();

        void move(SnakeDirection dir);

        boolean checkHeadColliding();

        boolean getDead();

        int16_t getLength();

        boolean checkFoodCollision(Position foodPos);

        void addLength();

        Position getPositionNotInSnake();


    };
}


#endif //MUEK_ARGB_MATRIX_BOARD_SNAKE_H
