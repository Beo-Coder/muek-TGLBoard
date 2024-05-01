//
// Created by leo on 30.04.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SNAKEAI_H
#define MUEK_ARGB_MATRIX_BOARD_SNAKEAI_H

#include "Arduino.h"
#include "pioMatrixOutput.h"
#include "color.h"
#include "display_program.h"
#include "BeoCommon.h"

#define LENGTH_GROWTH 1
#define START_LENGTH 1


namespace details_snake_ai{




    class HamiltonianCircle{


        int pathIndex;

        void generateCircle();

        void generatePath();
        void backbite();

        void backbiteLeft(uint16_t step);
        void backbiteRight(uint16_t step);
        void reversePath(int i1, int i2);

        bool legalPosition(uint16_t node);


    public:
        uint16_t path[MATRIX_SIZE];
        HamiltonianCircle();
        void generate();

    };

    struct Position{
        int16_t posX;
        int16_t posY;
        int8_t directionX;
        int8_t directionY;
    } ;


    enum SnakeDirection{
        None = 0,
        Right = 1,
        Left = 2,
        Up = 4,
        Down = 8
    };


    class Food{
        Position position;
    public:
        Food();
        Position getPosition();
        void setPosition(Position pos);
    };

    class Snake{
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



class snakeAI : public display_program{
    details_snake_ai::Snake snake;
    details_snake_ai::Food food;
    details_snake_ai::HamiltonianCircle path;


    boolean stopDead = false;
    uint8_t moves = 0;
    bool firstTime;

    void placeNewFood();

public:

    snakeAI(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);
    void refresh() override;
    void button1ISR(bool state) override;
    void button2ISR(bool state) override;
    void restart() override;


};


#endif //MUEK_ARGB_MATRIX_BOARD_SNAKEAI_H
