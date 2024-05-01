//
// Created by leo on 30.04.24.
//

#include "snakeAI.h"


details_snake_ai::HamiltonianCircle::HamiltonianCircle() {
    pathIndex = 0;
    for(int i=0; i<MATRIX_SIZE;i++){
        path[i] = 0;
    }

}

void details_snake_ai::HamiltonianCircle::generatePath() {
    path[0] = 0;
    pathIndex = 1;
    int nattempts = 1 + 1.0 * 10.0 * MATRIX_SIZE * std::pow(std::log(2. + MATRIX_SIZE), 2);
    Serial.println(nattempts);
    while (pathIndex < MATRIX_SIZE) {
        for (int i = 0; i < nattempts; i++) {
            backbite();
        }
    }


}

void details_snake_ai::HamiltonianCircle::backbite() {
    uint16_t step;
    switch (randomInt(0,4)) {
        case 0:
            step = 1;
            break;
        case 1:
            step = -1;
            break;
        case 2:
            step = 1<<8;
            break;
        case 3:
            step = -(1<<8);
            break;
    }

    if (randomInt(0,2)) {
        backbiteLeft(step);
    } else {
        backbiteRight(step);
    }
}

void details_snake_ai::HamiltonianCircle::backbiteLeft(uint16_t step) {
    uint16_t neighbour = path[0]+step;
    if(legalPosition(neighbour)){
        bool alreadyInPath = false;
        int i;
        for(i=1; i<pathIndex;i++){
            if(neighbour == path[i]){
                alreadyInPath = true;
                break;
            }

        }
        if(alreadyInPath){
            reversePath(0, i-1);
        }else{
            reversePath(0,pathIndex-1);
            path[pathIndex] = neighbour;
            pathIndex++;
        }
    }


}

void details_snake_ai::HamiltonianCircle::backbiteRight(uint16_t step) {
    uint16_t neighbour = path[pathIndex-1]+step;
    if(legalPosition(neighbour)){
        bool alreadyInPath = false;
        int i;
        for(i=pathIndex-2; i>=0;i--){
            if(neighbour == path[i]){
                alreadyInPath = true;
                break;
            }

        }
        if(alreadyInPath){
            reversePath(i+1, pathIndex-1);
        }else{
            path[pathIndex] = neighbour;
            pathIndex++;
        }
    }

}

void details_snake_ai::HamiltonianCircle::reversePath(int i1, int i2) {

    int jlim = (i2-i1+1)/2;
    uint16_t temp;
    for (int j=0; j<jlim; j++)
    {
        temp = path[i1+j];
        path[i1+j] = path[i2-j];
        path[i2-j] = temp;
    }

}

void details_snake_ai::HamiltonianCircle::generate() {
    generateCircle();
    for(int i=0; i<MATRIX_SIZE;i++){
        Serial.print(path[i]);
        Serial.print(" ");
    }
    Serial.print("\n\r");

}

bool details_snake_ai::HamiltonianCircle::legalPosition(uint16_t node) {

    //if((index/LENGTH == pathIndex/LENGTH && index%LENGTH >= (pathIndex-1)%LENGTH && index%LENGTH <= (pathIndex+1)%LENGTH)) return false;
    //if((index%LENGTH == pathIndex%LENGTH && index/LENGTH >= (pathIndex-1)/LENGTH && index/LENGTH <= (pathIndex+1)/LENGTH)) return false;

    // if(pathIndex/MATRIX_LENGTH != index/(MATRIX_LENGTH)) return false;
    // if(pathIndex/MATRIX_HEIGHT != index/(MATRIX_HEIGHT)) return false;


    uint16_t x=node&0xFF;
    uint16_t y=(node>>8)&0xFF;

    if(x<0) return false;
    if(x>=MATRIX_LENGTH) return false;
    if(y<0) return false;
    if(y>=MATRIX_HEIGHT) return false;


/*
    if(index < 0) return false;
    if(index >= MATRIX_SIZE) return false;

    if(index/LENGTH + 1 == path[pathIndex-1]/LENGTH && index%LENGTH != path[pathIndex-1]%LENGTH) return false;
    if(index/LENGTH - 1 == path[pathIndex-1]/LENGTH && index%LENGTH != path[pathIndex-1]%LENGTH) return false;
*/
    //if(index/(MATRIX_LENGTH) > (MATRIX_HEIGHT)) return false;
    //if(index/(MATRIX_LENGTH) < 0) return false;

    //if((pathIndex-1)/LENGTH >= index/(LENGTH) && (pathIndex+1)/LENGTH <= index/(LENGTH) && pathIndex%LENGTH != index%(LENGTH)) return false;
    //if((pathIndex-1)%LENGTH >= index%(LENGTH) && (pathIndex+1)%LENGTH <= index%(LENGTH) && pathIndex/LENGTH != index/(LENGTH)) return false;
    return true;
}

void details_snake_ai::HamiltonianCircle::generateCircle() {
    generatePath();
    int min_dist = 1 + (pathIndex % 2);
    while (abs(path[pathIndex - 1] - path[0]) != min_dist) {
    // while (path[pathIndex - 1] - path[0] != min_dist) {
        backbite();
    }


}






snakeAI::snakeAI(MatrixOutput *ledMatrix, Color (*frame)[8][16]) : display_program(ledMatrix, frame) {
    clearFrame();
    refreshSpeed = 200;
    firstTime = true;

    //path.generate();
    //snake.setPosition(path.path[0]%MATRIX_LENGTH, path.path[0]/MATRIX_LENGTH);
    //moves = 1;




}


void isLegal(uint16_t * path){
    for(int i=1; i<MATRIX_SIZE; i++){

        int deltaX =  (int(path[i]&0xFF) - int(path[i-1]&0xFF))*(int(path[i]&0xFF) - int(path[i-1]&0xFF));
        int deltaY = (int((path[i]>>8)&0xFF) - int((path[i-1]>>8)&0xFF))*(int((path[i]>>8)&0xFF) - int((path[i-1]>>8)&0xFF));
/*
        Serial.print(path[i]%MATRIX_LENGTH);
        Serial.print(" ");
        Serial.print(path[i-1]%MATRIX_LENGTH);
        Serial.print(" ");


        Serial.print(path[i]/MATRIX_LENGTH - path[i-1]/MATRIX_LENGTH);
        Serial.print(" ");
        Serial.print(" ");
*/
        Serial.print(deltaX);
        Serial.print(" ");
        Serial.print(deltaY);
        Serial.print(" \n\r");


        if(deltaX == deltaY){
            Serial.print("Illegal move: ");
            Serial.print(i);
            Serial.print("\n\r");
        }


    }
}


void snakeAI::refresh() {

    if(firstTime){
        firstTime = false;
        path.generate();
        isLegal(path.path);

        snake.setPosition(path.path[0]&0xFF, (path.path[0]>>8)&0xFF);
        moves = 1;
    }



    if(!snake.getDead()){
        details_snake_ai::Position snakePos = snake.getPosition();
        details_snake_ai::Position nextMovePos;
        nextMovePos.posX = path.path[moves]&0xFF;
        nextMovePos.posY = (path.path[moves]>>8)&0xFF;

        if(nextMovePos.posX > snakePos.posX){
            snake.move(details_snake_ai::Right);
        }else if(nextMovePos.posX < snakePos.posX){
            snake.move(details_snake_ai::Left);
        }if(nextMovePos.posY > snakePos.posY){
            snake.move(details_snake_ai::Up);
        }else if(nextMovePos.posY < snakePos.posY){
            snake.move(details_snake_ai::Down);
        }



        moves = (moves +1)%MATRIX_SIZE;


        if(snake.checkFoodCollision(food.getPosition())){
            snake.addLength();
            placeNewFood();
        }



    }else if(!stopDead){
        Serial.println("Snake dead!");
        stopDead = true;
    }
    if(!snake.getDead()){
        clearFrame();
        (*frame)[MATRIX_HEIGHT - snake.snakeBody[0].posY - 1][snake.snakeBody[0].posX] = Color(1,2,0);
        for(int i=1;i<snake.getLength();i++){
            (*frame)[MATRIX_HEIGHT - snake.snakeBody[i].posY - 1][snake.snakeBody[i].posX] = colorGreen;
        }
        (*frame)[MATRIX_HEIGHT - food.getPosition().posY - 1][food.getPosition().posX] = colorRed;
    }

    matrix->setDisplayData(frame);
    matrix->sendData();



}

void snakeAI::button1ISR(bool state) {


}

void snakeAI::button2ISR(bool state) {

}

void snakeAI::restart() {

}



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

void snakeAI::placeNewFood() {

    food.setPosition(snake.getPositionNotInSnake());
    Serial.println("New food placed");
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



details_snake_ai::Food::Food() {
    position.posX = 8;
    position.posY = 5;

}

details_snake_ai::Position details_snake_ai::Food::getPosition() {
    return position;
}

void details_snake_ai::Food::setPosition(Position pos) {
    position.posX = pos.posX;
    position.posY = pos.posY;

}


