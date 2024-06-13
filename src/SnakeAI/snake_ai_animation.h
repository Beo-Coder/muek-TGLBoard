//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_SNAKE_AI_SNAKE_AI_ANIMATION_H
#define TGL_BOARD_SNAKE_AI_SNAKE_AI_ANIMATION_H


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "display_program.h"

#include "snake.h"
#include "food.h"
#include "hamiltonian_circle.h"








inline Color *snakeColor = &colorGreen;
inline Color *snakeHeadColor = &colorGreen;
inline Color *foodColor = &colorRed;







class SnakeAI : public DisplayProgram{
    details_snake_ai::Snake snake;
    details_snake_ai::Food food;
    details_snake_ai::HamiltonianCircle hamiltonianCircle;


    bool stopDead = false;
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


#endif //TGL_BOARD_SNAKE_AI_SNAKE_AI_ANIMATION_H
