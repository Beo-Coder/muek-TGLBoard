//
// Created by leo on 01.05.24.
//

#include "snake_ai_animation.h"

snakeAI::snakeAI(MatrixOutput *ledMatrix, Color (*frame)[8][16]) : display_program(ledMatrix, frame) {
    refreshSpeed = 0;
    firstTime = true;
    moves = 0;

    winCount = 0;
    failCount = 0;
    playCount = 0;
    averageTime = 0;
    averageTime = 0;
    numberPaths = 0;

    secondCoreState = 0;


}


void snakeAI::refresh() {

    uint32_t startMillis = millis();

    hamiltonianCircle.generate();

    uint32_t endMillis = millis();
    averageTime += endMillis - startMillis;
    if(endMillis - startMillis > highestTime){
        highestTime = endMillis - startMillis;
    }
    numberPaths++;

    Serial.print("\n\r-----------------------------------");
    Serial.print("\n\rAverage time: ");
    Serial.print(averageTime/numberPaths);
    Serial.print("\n\rHighest time: ");
    Serial.print(highestTime);
    Serial.print("\n\rNumber calculated: ");
    Serial.print(numberPaths);
    Serial.print("\n\r-----------------------------------");


/*


    if (firstTime) {
        playCount++;
        firstTime = false;
        hamiltonianCircle.generate();

        snake.setPosition(getXPos(hamiltonianCircle.path[0]), getYPos(hamiltonianCircle.path[0]));
        moves = 1;
    }


    if (!snake.getDead()) {
        uint16_t snakePos = snake.getPosition();
        uint8_t snakePosX = snakePos & 0xFF;
        uint8_t snakePosY = (snakePos >> 8) & 0xFF;
        if (snake.getLength() <= MATRIX_SIZE * 0.9) {
            // calcNextAIMove();
        }


        uint8_t nextMovePosX = hamiltonianCircle.path[moves] & 0xFF;
        uint8_t nextMovePosY = (hamiltonianCircle.path[moves] >> 8) & 0xFF;

        if (nextMovePosX > snakePosX) {
            // Serial.println("Right");
            snake.move(details_snake_ai::Right);
        } else if (nextMovePosX < snakePosX) {
            // Serial.println("Left");
            snake.move(details_snake_ai::Left);
        }
        if (nextMovePosY > snakePosY) {
            // Serial.println("Up");
            snake.move(details_snake_ai::Up);
        } else if (nextMovePosY < snakePosY) {
            // Serial.println("Down");
            snake.move(details_snake_ai::Down);
        }


        moves = (moves + 1) % MATRIX_SIZE;


        if (snake.checkFoodCollision(food.getPosition())) {
            snake.addLength();
            if (snake.getLength() >= MATRIX_SIZE) {
                winCount++;
                return restart();
            } else {
                placeNewFood();
            }

        }


    } else if (!stopDead) {
        failCount++;
        stopDead = true;
        return restart();
    }
    if (!snake.getDead()) {
        clearFrame();
        uint8_t posX = snake.snakeBody[0] & 0xFF;
        uint8_t posY = (snake.snakeBody[0] >> 8) & 0xFF;

        (*frame)[MATRIX_HEIGHT - posY - 1][posX] = Color(1, 2, 0);
        for (int i = 1; i < snake.getLength(); i++) {
            posX = snake.snakeBody[i] & 0xFF;
            posY = (snake.snakeBody[i] >> 8) & 0xFF;
            (*frame)[MATRIX_HEIGHT - posY - 1][posX] = colorGreen;
        }

        posX = food.getPosition() & 0xFF;
        posY = (food.getPosition() >> 8) & 0xFF;

        (*frame)[MATRIX_HEIGHT - posY - 1][posX] = colorRed;
    }

    matrix->setDisplayData(frame);
    matrix->sendData();


*/
}

/*
 * Calc next move by checking all positions next to head.
 * Check if the postions are legal, by checking if the snake remains ordered after the potential move.
 * Calc all the distances from the potential positions to the food.
 * Selecting the positions, which is legal and has the shortest distance to the food.
 */
void snakeAI::calcNextAIMove() {



    // Get postions next to head
    uint16_t posNextToHead[4];
    posNextToHead[0] = snake.getPosition() + 1; // Right
    posNextToHead[1] = snake.getPosition() - 1; // Left
    posNextToHead[2] = snake.getPosition() + (1 << 8); // Up
    posNextToHead[3] = snake.getPosition() - (1 << 8); // Down

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

bool snakeAI::aiCheckIfSnakeOrdered(uint16_t potentialMovePathIndex) {
    uint16_t snakeHeadPathIndex = getPathIndex(snake.getPosition());
    uint16_t snakeTailPathIndex = getPathIndex(snake.snakeBody[snake.getLength() - 1]);

    if (snakeHeadPathIndex > snakeTailPathIndex) {
        // [_____|======|_____]

        if (potentialMovePathIndex <= snakeHeadPathIndex && potentialMovePathIndex >= snakeTailPathIndex - 1) {
            return false;
        }
    } else {
        // [===|__________|===]

        if (potentialMovePathIndex <= snakeHeadPathIndex || potentialMovePathIndex >= snakeTailPathIndex - 1) {
            return false;
        }
    }

    return true;
}

uint16_t snakeAI::aiGetDistanceFood(uint16_t potentialMovePathIndex) {
    uint16_t distance;
    uint16_t pathIndexFood = getPathIndex(food.getPosition());

    distance = pathIndexFood - potentialMovePathIndex;
    if (distance < 0) {
        distance = MATRIX_SIZE - abs(distance);
    }
    return distance;
}


uint16_t snakeAI::getPathIndex(uint16_t pos) {
    for (uint16_t i = 0; i < MATRIX_SIZE; i++) {
        // if (hamiltonianCircle.path[i] == pos) {
            return i;
        // }
    }
    return MATRIX_SIZE;
}

uint8_t snakeAI::getXPos(uint16_t pos) {
    return pos & 0xFF;
}

uint8_t snakeAI::getYPos(uint16_t pos) {
    return (pos >> 8) & 0xFF;
}


void snakeAI::placeNewFood() {

    food.setPosition(snake.getPositionNotInSnake());
    // Serial.println("New food placed");
}


void snakeAI::button1ISR(bool state) {


}

void snakeAI::button2ISR(bool state) {

}

void snakeAI::restart() {
    snake.reset();
    firstTime = true;
    stopDead = false;
/*
    Serial.print("\n\r--------------------------");
    Serial.print("\n\rPlayed games: ");
    Serial.print(playCount);
    Serial.print("\n\rWon games: ");
    Serial.print(winCount);
    Serial.print("\n\Failed games: ");
    Serial.print(failCount);
    Serial.print("\n\r--------------------------\n\r");
    */



}








