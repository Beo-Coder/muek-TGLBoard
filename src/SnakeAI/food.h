//
// Created by leo on 01.05.24.
//

#ifndef TGL_BOARD_SNAKE_AI_FOOD_H
#define TGL_BOARD_SNAKE_AI_FOOD_H

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif



namespace details_snake_ai {
    class Food {
        uint16_t position;
    public:
        Food();

        uint16_t getPosition() const;

        void setPosition(uint16_t pos);
    };
}


#endif //TGL_BOARD_SNAKE_AI_FOOD_H
