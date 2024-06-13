//
// Created by leo on 25.05.24.
//

#ifndef TGL_BOARD_METEORITE_ANIMATION_METEORITE_ANIMATION_H
#define TGL_BOARD_METEORITE_ANIMATION_METEORITE_ANIMATION_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif

#include "display_program.h"

namespace details_meteorite_animation{

    inline const float BRIGHTNESS_FACTOR = 2.0;
    inline const uint8_t MAX_NUMBER_METEORITE_TRAILS = 20;
    inline const uint8_t MIN_DISTANCE_TRAILS = 2;
    inline const uint8_t MIN_TIME_NEW_TRAIL = 0;
    inline const uint8_t MAX_TIME_NEW_TRAIL = 2;


    struct Meteorite{
        uint8_t length;
        uint8_t posX;
        uint8_t posY;
        bool alive;
    };

}


class MeteoriteAnimation : public DisplayProgram{

    Color pixelColor;

    details_meteorite_animation::Meteorite trails[details_meteorite_animation::MAX_NUMBER_METEORITE_TRAILS];



    void newTrail();

    uint8_t counterNewTrail;

    uint8_t getYPos();

    Color* getColor(uint8_t posX);

public:

    explicit MeteoriteAnimation(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);


    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;

};


#endif //TGL_BOARD_METEORITE_ANIMATION_METEORITE_ANIMATION_H
