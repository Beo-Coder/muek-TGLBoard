//
// Created by leo on 27.04.24.
//

#include "firework_animation.h"
#include "firework.h"
#include "beo_common.h"



FireworkAnimation::FireworkAnimation(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) : display_program(ledMatrix, frame) {
    refreshSpeed = SIMULATION_SPEED;
    timeSinceLastFirework = 0;
    lastFireWorkPostion = 0;
    fireworkColor = 0;

    for(details_firework::Firework* & i : firework){
        i = new details_firework::Firework();
    }
    clearFrame();


}



void FireworkAnimation::refresh() {
    calcFrame();

    matrix->setDisplayData(frame);
    matrix->sendData();


}

void FireworkAnimation::calcFrame() {
    if (timeSinceLastFirework >= TIME_BETWEEN_FIREWORKS) {
        createNewFirework();
    }
    timeSinceLastFirework++;
    clearFrame();

    for (details_firework::Firework* & i : firework) {
        i->calcFrame(frame);
    }


}

void FireworkAnimation::createNewFirework() {
    // Get "random" location (not to near to previous firework)
    uint8_t postion = beo::randomInt(0, NUMBER_POSITIONS);
    uint8_t tries = 0;
    while (lastFireWorkPostion + MIN_SPACE_BETWEEN_POSTIONS >= postion &&
           lastFireWorkPostion - MIN_SPACE_BETWEEN_POSTIONS <= postion && tries < 50) {
        postion = beo::randomInt(0, NUMBER_POSITIONS);
        tries++;
    }

    addNewFirework(postions[postion], beo::randomInt(FIREWORK_EXPLODE_Y_MIN, FIREWORK_EXPLODE_Y_MAX), randomColor[fireworkColor]);

    timeSinceLastFirework = 0;
    lastFireWorkPostion = postion;
    fireworkColor = (fireworkColor + beo::randomInt(1,NUMBER_FIREWORK_COLORS/2)) % NUMBER_FIREWORK_COLORS;

}

void FireworkAnimation::addNewFirework(int8_t explodePosX, int8_t explodePosY, Color *color) {
    for (details_firework::Firework* & i : firework) {
        if (i->dead) {
            i->start(explodePosX, explodePosY, color);
            break;
        }
    }
}


void FireworkAnimation::button1ISR(bool state) {

}

void FireworkAnimation::button2ISR(bool state) {

}

void FireworkAnimation::restart() {

}



