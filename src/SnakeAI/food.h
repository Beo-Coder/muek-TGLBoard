//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_FOOD_H
#define MUEK_ARGB_MATRIX_BOARD_FOOD_H

#include <Arduino.h>



namespace details_snake_ai {
    class Food {
        uint16_t position;
    public:
        Food();

        uint16_t getPosition() const;

        void setPosition(uint16_t pos);
    };
}


#endif //MUEK_ARGB_MATRIX_BOARD_FOOD_H
