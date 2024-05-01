//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_SNAKEAIANIMATION_H
#define MUEK_ARGB_MATRIX_BOARD_SNAKEAIANIMATION_H



#include "Arduino.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "color.h"
#include "display_program.h"
#include "BeoCommon.h"

#include "snake_ai_settings.h"
#include "hamiltonian_circle.h"
#include "snake.h"
#include "food.h"








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


};;


#endif //MUEK_ARGB_MATRIX_BOARD_SNAKEAIANIMATION_H
