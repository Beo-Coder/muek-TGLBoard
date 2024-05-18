//
// Created by leo on 27.04.24.
//

#ifndef TGL_BOARD_FIREWORK_FIREWORK_ANIMATION_H
#define TGL_BOARD_FIREWORK_FIREWORK_ANIMATION_H

namespace details_firework{
    class Firework;
}

#include <Arduino.h>
#include "display_program.h"
#include "firework_settings.h"




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


#endif //TGL_BOARD_FIREWORK_FIREWORK_ANIMATION_H
