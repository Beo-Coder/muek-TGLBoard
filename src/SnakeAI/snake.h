//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_SNAKE_AI_SNAKE_H
#define TGL_BOARD_SNAKE_AI_SNAKE_H

#include <Arduino.h>
#include "PIOMatrixOutput/pio_matrix_settings.h"

#include "snake_ai_settings.h"

namespace details_snake_ai {
    class Snake {
        bool dead;

        int16_t length;


    public:
        uint16_t snakeBody[MATRIX_SIZE];

        Snake();

        void setPosition(int16_t posX, int16_t posY);

        uint16_t getPosition();

        void move(Direction dir);

        boolean checkHeadColliding();

        boolean getDead() const;

        int16_t getLength() const;

        boolean checkFoodCollision(uint16_t foodPos);

        void addLength();

        uint16_t getPositionNotInSnake();

        bool checkCollision(uint16_t pos);

        void reset();


    };
}


#endif //TGL_BOARD_SNAKE_AI_SNAKE_H
