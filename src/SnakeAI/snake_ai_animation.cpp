//
// Created by leo on 01.05.24.
//

#include "snake_ai_animation.h"

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

void snakeAI::placeNewFood() {

    food.setPosition(snake.getPositionNotInSnake());
    Serial.println("New food placed");
}


void snakeAI::button1ISR(bool state) {


}

void snakeAI::button2ISR(bool state) {

}

void snakeAI::restart() {

}