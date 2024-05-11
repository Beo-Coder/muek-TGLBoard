//
// Created by leo on 01.05.24.
//

#include "food.h"

details_snake_ai::Food::Food() {
   position = (6 << 8) | 5;

}

uint16_t details_snake_ai::Food::getPosition() const {
    return position;
}

void details_snake_ai::Food::setPosition(uint16_t pos) {
    position = pos;

}