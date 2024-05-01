//
// Created by leo on 01.05.24.
//

#include "food.h"

details_snake_ai::Food::Food() {
    position.posX = 8;
    position.posY = 5;

}

details_snake_ai::Position details_snake_ai::Food::getPosition() {
    return position;
}

void details_snake_ai::Food::setPosition(Position pos) {
    position.posX = pos.posX;
    position.posY = pos.posY;

}