//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_FIREWORK_FIREWORK_ANIMATION_H
#define TGL_BOARD_FIREWORK_FIREWORK_ANIMATION_H

namespace details_firework{
    class Firework;
}


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "display_program.h"
#include "firework_settings.h"
#include "firework.h"




class FireworkAnimation : public DisplayProgram {



    uint8_t timeSinceLastFirework;
    uint8_t lastFireWorkPostion; // Index in position array
    uint8_t fireworkColor; // index in color array

    details_firework::Firework firework[details_firework::MAX_NUMBER_FIREWORKS];


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
