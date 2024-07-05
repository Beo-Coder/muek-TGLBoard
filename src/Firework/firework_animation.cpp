//
// © 2024 Leonhard Baschang
//

#include "firework_animation.h"
#include "firework.h"
#include "beo_common.h"



FireworkAnimation::FireworkAnimation(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) : DisplayProgram(ledMatrix, frame) {
    refreshSpeed = details_firework::SIMULATION_SPEED;
    timeSinceLastFirework = 0;
    lastFireWorkPostion = 0;
    fireworkColor = 0;

}



void FireworkAnimation::refresh() {
    calcFrame();

    matrix->setDisplayData(frame);
    matrix->sendData();


}

void FireworkAnimation::calcFrame() {
    if (timeSinceLastFirework >= details_firework::TIME_BETWEEN_FIREWORKS) {
        createNewFirework();
    }
    timeSinceLastFirework++;
    clearFrame();

    for (details_firework::Firework & i : firework) {
        i.calcFrame(frame);
    }


}

void FireworkAnimation::createNewFirework() {
    // Get "random" location (not to near to previous firework)
    uint8_t postion = beo::randomInt(0, details_firework::NUMBER_POSITIONS);
    uint8_t tries = 0;
    while (lastFireWorkPostion + details_firework::MIN_SPACE_BETWEEN_POSTIONS >= postion &&
           lastFireWorkPostion - details_firework::MIN_SPACE_BETWEEN_POSTIONS <= postion && tries < 50) {
        postion = beo::randomInt(0, details_firework::NUMBER_POSITIONS);
        tries++;
    }

    addNewFirework(details_firework::postions[postion], beo::randomInt(details_firework::FIREWORK_EXPLODE_Y_MIN, details_firework::FIREWORK_EXPLODE_Y_MAX), details_firework::randomColor[fireworkColor]);

    timeSinceLastFirework = 0;
    lastFireWorkPostion = postion;
    fireworkColor = (fireworkColor + beo::randomInt(1,details_firework::NUMBER_FIREWORK_COLORS/2)) % details_firework::NUMBER_FIREWORK_COLORS;

}

void FireworkAnimation::addNewFirework(int8_t explodePosX, int8_t explodePosY, Color *color) {
    for (details_firework::Firework & i : firework) {
        if (i.dead) {
            i.start(explodePosX, explodePosY, color);
            break;
        }
    }
}


void FireworkAnimation::button1ISR(bool state) {

}

void FireworkAnimation::button2ISR(bool state) {

}

void FireworkAnimation::restart() {
    timeSinceLastFirework = 0;
    lastFireWorkPostion = 0;
    fireworkColor = 0;
    for (details_firework::Firework & i : firework) {
        i.reset();
    }

}



