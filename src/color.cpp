//
// Created by leo on 03.04.24.
//

#include "color.h"

uint32_t Color::calc() {


    return ((uint32_t)this->green << 16) | ((uint32_t)this->red << 8) | ((uint32_t)this->blue);

}

float Color::getRed() {
    return red;
}
