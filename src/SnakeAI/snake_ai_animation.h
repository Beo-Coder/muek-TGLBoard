//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SNAKEAIANIMATION_H
#define MUEK_ARGB_MATRIX_BOARD_SNAKEAIANIMATION_H


#include <Arduino.h>
#include "display_program.h"

#include "snake.h"
#include "food.h"
#include "hamiltonian_circle.h"








static Color *snakeColor = &colorGreen;
static Color *foodColor = &colorRed;







class SnakeAI : public display_program{
    details_snake_ai::Snake snake;
    details_snake_ai::Food food;
    details_snake_ai::HamiltonianCircle hamiltonianCircle;


    boolean stopDead = false;
    uint8_t moves;

    void placeNewFood();

    void renderFrame();

    uint16_t getPathIndex(uint16_t pos);

    // AI functions
    void calcNextAIMove();
    bool aiCheckIfSnakeOrdered(uint16_t potentialMovePathIndex);
    uint16_t aiGetDistanceFood(uint16_t potentialMovePathIndex);


    static uint8_t getXPos(uint16_t pos);
    static uint8_t getYPos(uint16_t pos);



public:

    SnakeAI(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);
    void refresh() override;
    void button1ISR(bool state) override;
    void button2ISR(bool state) override;
    void restart() override;


};


#endif //MUEK_ARGB_MATRIX_BOARD_SNAKEAIANIMATION_H
