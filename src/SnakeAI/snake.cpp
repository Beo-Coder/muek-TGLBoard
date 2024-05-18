//
// Created by leo on 01.05.24.
//

#include "snake.h"
#include "BeoCommon.h"

details_snake_ai::Snake::Snake() {
    reset();
}


void details_snake_ai::Snake::reset() {
    length = START_LENGTH;
    snakeBody[0] = (5 << 8) | 5;
    for(int i=1;i<MATRIX_SIZE;i++){
        snakeBody[i] = -(1 << 8) | (-1);

    }
    dead = false;

}


void details_snake_ai::Snake::setPosition(int16_t posX, int16_t posY) {
    snakeBody[0] = (posY << 8) | posX;

}
uint16_t details_snake_ai::Snake::getPosition() {
    return snakeBody[0];
}




void details_snake_ai::Snake::move(details_snake_ai::Direction dir) {
    int8_t x = 0;
    int8_t y = 0;

    switch (dir) {
        case Right:
            x++;
            break;
        case Left:
            x--;
            break;
        case Up:
            y++;
            break;
        case Down:
            y--;
            break;
        case None:
            break;
    }



    for(int i=length-1;i>0;i--){

        snakeBody[i] = snakeBody[i-1];
    }

    snakeBody[0] += x;
    snakeBody[0] += y << 8;

    if(checkHeadColliding()){
        dead = true;
    }


}




bool
details_snake_ai::Snake::checkHeadColliding() {
    uint8_t snakeX = snakeBody[0] & 0xFF;
    uint8_t snakeY = (snakeBody[0] >> 8) & 0xFF;

    if(snakeX < 0 || snakeX >= MATRIX_LENGTH || snakeY < 0 || snakeY >= MATRIX_HEIGHT){
        return true;
    }
    for(int i=1;i<length;i++){
        if(snakeBody[0] == snakeBody[i]){
            return true;
        }
    }

    return false;
}





bool details_snake_ai::Snake::getDead() const {
    return dead;
}

int16_t details_snake_ai::Snake::getLength() const {
    return length;
}

bool details_snake_ai::Snake::checkFoodCollision(uint16_t foodPos) {
    return foodPos == snakeBody[0];
}

void details_snake_ai::Snake::addLength() {
    snakeBody[length] = snakeBody[length-1];
    length += LENGTH_GROWTH;
}

uint16_t details_snake_ai::Snake::getPositionNotInSnake() {

    uint8_t posX;
    uint8_t posY;
    uint8_t snakeX;
    uint8_t snakeY;

    uint16_t positions[MATRIX_SIZE];
    uint16_t numberPositions = 0;
    bool inSnake = false;

    for(uint16_t i=0; i<MATRIX_SIZE; i++){
        posX = i%MATRIX_LENGTH;
        posY = i/MATRIX_LENGTH;
        for(int k=0; k<length;k++){
            snakeX = snakeBody[k] & 0xFF;
            snakeY = (snakeBody[k] >> 8) & 0xFF;
            if(snakeX == posX && snakeY == posY){
                inSnake = true;
                break;
            }

        }
        if(!inSnake) {
            positions[numberPositions] = i;
            numberPositions++;
        }
        inSnake = false;
    }


    uint16_t randomPositionIndex = beo::randomInt(0, numberPositions);
    posX = positions[randomPositionIndex]%MATRIX_LENGTH;
    posY = positions[randomPositionIndex]/MATRIX_LENGTH;

    return (posY << 8) | posX;
}

bool details_snake_ai::Snake::checkCollision(uint16_t pos) {
    for(int i=0; i<length;i++){
        if(snakeBody[i] == pos){
            return true;
        }
    }
    return false;
}


