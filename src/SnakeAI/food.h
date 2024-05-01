//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_FOOD_H
#define MUEK_ARGB_MATRIX_BOARD_FOOD_H

#include "Arduino.h"
#include "snake_ai_settings.h"


namespace details_snake_ai {
    class Food {
        Position position;
    public:
        Food();

        Position getPosition();

        void setPosition(Position pos);
    };
}


#endif //MUEK_ARGB_MATRIX_BOARD_FOOD_H
