//
// © 2024 Leonhard Baschang
//

#include "entity.h"
details_dino_game::Entity::Entity(int8_t startPosX, int8_t startPosY, int8_t sizeX, int8_t sizeY) {
    posX = startPosX;
    posY = startPosY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;

}

details_dino_game::Entity::Entity() {
    posX = -1;
    posY = -1;
    sizeX = 0;
    sizeY = 0;
}
