//
// Created by leo on 01.05.24.
//

#include "snake.h"

details_snake_ai::Snake::Snake() {
    length = 3;
    snakeBody[0].posX = 5;
    snakeBody[0].posY = 5;
    for(int i=1;i<MATRIX_SIZE;i++){
        snakeBody[i].posX = -5;
        snakeBody[i].posY = -5;

    }
    dead = false;

}


void details_snake_ai::Snake::setPosition(int16_t posX, int16_t posY) {
    snakeBody[0].posX = posX;
    snakeBody[0].posY = posY;

}
details_snake_ai::Position details_snake_ai::Snake::getPosition() {
    return snakeBody[0];
}




void details_snake_ai::Snake::move(details_snake_ai::SnakeDirection dir) {
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
        snakeBody[i].posX = snakeBody[i-1].posX;
        snakeBody[i].posY = snakeBody[i-1].posY;

    }
    snakeBody[0].posX += x;
    snakeBody[0].posY += y;

    if(checkHeadColliding()){
        dead = true;
    }


}




boolean details_snake_ai::Snake::checkHeadColliding() {
    if(snakeBody[0].posX < 0 || snakeBody[0].posX >= MATRIX_LENGTH || snakeBody[0].posY < 0 || snakeBody[0].posY >= MATRIX_HEIGHT){
        return true;
    }
    for(int i=1;i<length;i++){
        if(snakeBody[0].posX == snakeBody[i].posX && snakeBody[0].posY == snakeBody[i].posY){
            return true;
        }
    }

    return false;
}





boolean details_snake_ai::Snake::getDead() {
    return dead;
}

int16_t details_snake_ai::Snake::getLength() {
    return length;
}

boolean details_snake_ai::Snake::checkFoodCollision(Position foodPos) {
    return foodPos.posX == snakeBody[0].posX && foodPos.posY == snakeBody[0].posY;
}

void details_snake_ai::Snake::addLength() {
    length++;
}

details_snake_ai::Position details_snake_ai::Snake::getPositionNotInSnake() {
    Position pos;
    boolean posInsideSnake;

    do{
        pos.posX = int16_t(randomInt(0,MATRIX_LENGTH));
        pos.posY = int16_t(randomInt(0,MATRIX_HEIGHT));
        posInsideSnake = false;
        for(int i=0; i<length;i++){
            if(snakeBody[i].posX == pos.posX && snakeBody[i].posY == pos.posY){
                posInsideSnake = true;
                break;
            }
        }


    }while(posInsideSnake);

    return pos;
}