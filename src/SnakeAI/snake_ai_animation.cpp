//
// Created by leo on 01.05.24.
//

#include "snake_ai_animation.h"
#include "snake_ai_settings.h"
#include "beo_common.h"

SnakeAI::SnakeAI(MatrixOutput *ledMatrix, Color (*frame)[8][16]) : DisplayProgram(ledMatrix, frame) {
    refreshSpeed = 50;
    moves = 0;

}


void SnakeAI::refresh() {


    if (!snake.getDead()) {


        if (snake.getLength() <= MATRIX_SIZE * AI_MOVES_MAX_SNAKE_SIZE) {
            calcNextAIMove();
        }

        uint8_t snakePosX = getXPos(snake.getPosition());
        uint8_t snakePosY = getYPos(snake.getPosition());

        uint8_t nextMovePosX = getXPos(hamiltonianCircle.path[moves]);
        uint8_t nextMovePosY = getYPos(hamiltonianCircle.path[moves]);



        if (nextMovePosX > snakePosX) {
            snake.move(details_snake_ai::Right);
        } else if (nextMovePosX < snakePosX) {
            snake.move(details_snake_ai::Left);
        }else if (nextMovePosY > snakePosY) {
            snake.move(details_snake_ai::Up);
        } else if (nextMovePosY < snakePosY) {
            snake.move(details_snake_ai::Down);
        }


        moves = (moves + 1) % MATRIX_SIZE;


        if (snake.checkFoodCollision(food.getPosition())) {
            snake.addLength();

            if (snake.getLength() >= MATRIX_SIZE) {
                return restart();
            } else {
                placeNewFood();
            }

        }


    } else if (!stopDead) {
        stopDead = true;
        return restart();
    }


    if (!snake.getDead()) {
        clearFrame();
        renderFrame();

    }

    matrix->setDisplayData(frame);
    matrix->sendData();



}

void SnakeAI::renderFrame() {
    uint8_t posX = getXPos(snake.snakeBody[0]);
    uint8_t posY = getYPos(snake.snakeBody[0]);

    // Head postion (if head should have a different color)
    (*frame)[MATRIX_HEIGHT - posY - 1][posX] = *snakeHeadColor;



    uint8_t lastXPixels = LAST_X_PIXELS_DIMMER;
    // Body postion
    if(snake.getLength() > LAST_X_PIXELS_DIMMER){
        for (int i = 1; i <= snake.getLength()-LAST_X_PIXELS_DIMMER; i++) {
            posX = getXPos(snake.snakeBody[i]);
            posY = getYPos(snake.snakeBody[i]);
            (*frame)[MATRIX_HEIGHT - posY - 1][posX] = *snakeColor;
        }
    }else{
        lastXPixels = snake.getLength();
    }


    // The last X pixels have a different color
    Color tailColor;
    for (int i = snake.getLength()-lastXPixels+1; i < snake.getLength(); i++) {
        tailColor.set(snakeColor);
        uint8_t cycle = i-(snake.getLength()-lastXPixels);
        float data = (((float(NORMAL_BRIGHTNESS)/(float(lastXPixels+1)))*float(lastXPixels-cycle))/NORMAL_BRIGHTNESS);
        tailColor.multiply(data);
        posX = getXPos(snake.snakeBody[i]);
        posY = getYPos(snake.snakeBody[i]);
        (*frame)[MATRIX_HEIGHT - posY - 1][posX] = tailColor;
    }


    // Set food postion
    posX = getXPos(food.getPosition());
    posY = getYPos(food.getPosition());

    (*frame)[MATRIX_HEIGHT - posY - 1][posX] = *foodColor;

}

/*
 * Calc next move by checking all positions next to head.
 * Check if the postions are legal, by checking if the snake remains ordered after the potential move.
 * Calc all the distances from the potential positions to the food.
 * Selecting the positions, which is legal and has the shortest distance to the food.
 */
void SnakeAI::calcNextAIMove() {



    // Get postions next to head
    uint16_t posNextToHead[4];
    posNextToHead[0] = snake.getPosition() + details_snake_ai::Right; // Right
    posNextToHead[1] = snake.getPosition() + details_snake_ai::Left; // Left
    posNextToHead[2] = snake.getPosition() + details_snake_ai::Up; // Up
    posNextToHead[3] = snake.getPosition() + details_snake_ai::Down; // Down

    // path index for the potential moves
    uint16_t pathIndexPosNextToHead[4];

    // distances for the potential moves
    uint16_t distanceToFood[5];

    for (int i = 0; i < 4; i++) {
        // Get the path index to the positions
        pathIndexPosNextToHead[i] = getPathIndex(posNextToHead[i]);

        // Check if the snake remains ordered after the move.
        if (!aiCheckIfSnakeOrdered(pathIndexPosNextToHead[i])) {
            pathIndexPosNextToHead[i] = MATRIX_SIZE;
        }

        // Calculate the distance to the food from the postion
        distanceToFood[i] = aiGetDistanceFood(pathIndexPosNextToHead[i]);

    }


    // some high arbitrary distance for the highest distance to the food.
    distanceToFood[4] = MATRIX_SIZE * 2;
    uint8_t minDistanceFoodIndex = 4;

    for (int i = 0; i < 4; i++) {
        /* Check if the distance is smaller than the currently smallest distance.
         * Check if the move is legal, by checking if the position is != MATRIX_SIZE
         * Check if the move does not kill the snake by going into itself (maybe redundant)
         */
        if (distanceToFood[i] < distanceToFood[minDistanceFoodIndex] && pathIndexPosNextToHead[i] != MATRIX_SIZE &&
            !snake.checkCollision(posNextToHead[i])) {
            minDistanceFoodIndex = i;
        }
    }
    // If AI calculated a move, do it
    if (minDistanceFoodIndex != 4) {
        moves = pathIndexPosNextToHead[minDistanceFoodIndex];
    }


}

bool SnakeAI::aiCheckIfSnakeOrdered(uint16_t potentialMovePathIndex) {
    uint16_t snakeHeadPathIndex = getPathIndex(snake.getPosition());
    uint16_t snakeTailPathIndex = getPathIndex(snake.snakeBody[snake.getLength() - 1]);

    if (snakeHeadPathIndex > snakeTailPathIndex) {
        // [_____|======|_____]

        if (potentialMovePathIndex <= snakeHeadPathIndex && potentialMovePathIndex >= snakeTailPathIndex - AI_MOVES_MIN_DISTANCE_TAIL) {
            return false;
        }
    } else {
        // [===|__________|===]

        if (potentialMovePathIndex <= snakeHeadPathIndex || potentialMovePathIndex >= snakeTailPathIndex - AI_MOVES_MIN_DISTANCE_TAIL) {
            return false;
        }
    }

    return true;
}

uint16_t SnakeAI::aiGetDistanceFood(uint16_t potentialMovePathIndex) {
    int32_t distance;
    uint16_t pathIndexFood = getPathIndex(food.getPosition());

    distance = pathIndexFood - potentialMovePathIndex;
    if (distance < 0) {
        distance = MATRIX_SIZE - absolut(distance);
    }
    return distance;
}


uint16_t SnakeAI::getPathIndex(uint16_t pos) {
    for (uint16_t i = 0; i < MATRIX_SIZE; i++) {
        if (hamiltonianCircle.path[i] == pos) {
            return i;
        }
    }
    return MATRIX_SIZE;
}

uint8_t SnakeAI::getXPos(uint16_t pos) {
    return pos & 0xFF;
}

uint8_t SnakeAI::getYPos(uint16_t pos) {
    return (pos >> 8) & 0xFF;
}


void SnakeAI::placeNewFood() {
    food.setPosition(snake.getPositionNotInSnake());
}


void SnakeAI::button1ISR(bool state) {


}

void SnakeAI::button2ISR(bool state) {

}

void SnakeAI::restart() {
    snake.reset();
    stopDead = false;

    hamiltonianCircle.generate();

    snake.setPosition(getXPos(hamiltonianCircle.path[0]), getYPos(hamiltonianCircle.path[0]));
    moves = 1;

}










