//
// Created by leo on 03.04.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_COLOR_H
#define MUEK_ARGB_MATRIX_BOARD_COLOR_H

#include "Arduino.h"

class Color {
public:
    float blue;
    float red;
    float green;

    float getRed();

    uint32_t calc();
};


#endif //MUEK_ARGB_MATRIX_BOARD_COLOR_H
