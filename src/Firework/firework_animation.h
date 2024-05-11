//
// Created by leo on 27.04.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_FIREWORK_ANIMATION_H
#define MUEK_ARGB_MATRIX_BOARD_FIREWORK_ANIMATION_H

#include "pico/stdlib.h"
#include "PIOMatrixOutput/color.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "display_program.h"
#include "BeoCommon.h"

#include "firework_settings.h"
#include "pixel.h"
#include "firework.h"



class FireworkAnimation : public display_program {



    uint8_t timeSinceLastFirework;
    uint8_t lastFireWorkPostion; // Index in position array
    uint8_t fireworkColor; // index in color array

    details_firework::Firework *firework[MAX_NUMBER_FIREWORKS];


    void calcFrame();

    void createNewFirework();

    void addNewFirework(int8_t explodePosX, int8_t explodePosY, Color *color);


public:

    FireworkAnimation(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void refresh() override;
    void button1ISR(bool state) override;
    void button2ISR(bool state) override;
    void restart() override;


};


#endif //MUEK_ARGB_MATRIX_BOARD_FIREWORK_ANIMATION_H
