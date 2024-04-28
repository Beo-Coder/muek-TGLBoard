//
// Created by leo on 27.04.24.
//

#include "FireworkAnimation.h"

detailsFirework::Pixel::Pixel() {
    posX = -1;
    posY = -1;
    dirX = 0;
    dirY = 0;

}


detailsFirework::Firework::Firework() {
    dead = true;
    arrived = true;
    exploded = true;
    lifeTime = 0;
    startPosX = 0;
    startPosY = 0;
    for(Pixel* & i : pixel){
        i = new Pixel();
    }
}



void detailsFirework::Firework::start(int8_t posX, int8_t posY, Color *color) {
    lifeTime = 0;
    dead = false;
    arrived = false;
    exploded = false;

    this->startPosX = posX;
    this->startPosY = 0;

    // Configure each pixel
    for (int i = 0; i < PIXEL_PER_FIREWORK; i++) {
        pixel[i]->posX = posX;
        pixel[i]->posY = posY;

        // This could certainly be improved
        switch (i % 4) {
            case 0:
                pixel[i]->dirX = float(randomInt(0, FIREWORK_SPEED_VALUE_X + 1));
                pixel[i]->dirY = float(randomInt(0, FIREWORK_SPEED_VALUE_Y + 1));
                break;
            case 1:
                pixel[i]->dirX = float(randomInt(-FIREWORK_SPEED_VALUE_X, 0));
                pixel[i]->dirY = float(randomInt(0, FIREWORK_SPEED_VALUE_Y + 1));
                break;
            case 2:
                pixel[i]->dirX = float(randomInt(0, FIREWORK_SPEED_VALUE_X + 1));
                pixel[i]->dirY = float(randomInt(-FIREWORK_SPEED_VALUE_Y, 0));
                break;
            case 3:
                pixel[i]->dirX = float(randomInt(-FIREWORK_SPEED_VALUE_X, 0));
                pixel[i]->dirY = float(randomInt(-FIREWORK_SPEED_VALUE_Y, 0));
                break;
        }


        pixel[i]->color = *color;
    }

}

void detailsFirework::Firework::calcFrame(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    if (!exploded) {
        calcFireworkTrail(display);

    } else {
        calcFireworkExplosion(display);

    }

}

void detailsFirework::Firework::calcFireworkTrail(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {


    if(startPosY >= int(pixel[0]->posY)){
        arrived = true;
    }

    if(startPosY >= int(pixel[0]->posY)+TIME_DELAY_ARRIVAL_EXPLOSION){
        exploded = true;
    }

    uint8_t trailPosY = startPosY;

    if(arrived){
        trailPosY = int(pixel[0]->posY);
    }


    for(int i=0; i<PIXEL_PER_FIREWORK_TRAIL;i++){
        if(startPosY-i >=0 && startPosY-i < trailPosY){
            (*display)[MATRIX_HEIGHT - (startPosY-i) - 1][startPosX] = colorWhite;
        }
    }


    (*display)[MATRIX_HEIGHT - trailPosY - 1][startPosX] = colorWhite;

    startPosY++;



}

void detailsFirework::Firework::calcFireworkExplosion(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {

    if (lifeTime < FIREWORK_LIFE_TIME) {
        for (Pixel* & i : pixel) {
            int8_t posX = i->posX;
            int8_t posY = i->posY;

            i->posX += (i->dirX * (1 - (float(lifeTime) / FIREWORK_DECELERATION_VALUE_X))) /
                              FIREWORK_SPEED_VALUE_X2;
            i->posY += (i->dirY * (1 - (float(lifeTime) / FIREWORK_DECELERATION_VALUE_Y))) /
                              FIREWORK_SPEED_VALUE_Y2 - FIREWORK_SINK_RATE;

            // Only add to frame, when pixel is inside frame
            if (posX >= 0 && posX < MATRIX_LENGTH && posY >= 0 && posY < MATRIX_HEIGHT) {
                (*display)[MATRIX_HEIGHT - posY - 1][posX] = i->color;
            }

        }
        lifeTime++;
    }else{
        dead = true;
    }

}


FireworkAnimation::FireworkAnimation(MatrixOutput *ledMatrix) {
    matrix = ledMatrix;
    refreshSpeed = SIMULATION_SPEED;
    timeSinceLastFirework = 0;
    lastFireWorkPostion = 0;
    fireworkColor = 0;

    for(detailsFirework::Firework* & i : firework){
        i = new detailsFirework::Firework();
    }
    blankFrame();


    colorBla.red = 1;
    colorBla2.blue = 1;
    colorBla3.green = 1;
    colorBla4.blue = 1;
    colorBla4.green = 1;

    colorWhite.red = 1;
    colorWhite.green = 1;
    colorWhite.blue = 1;


}



void FireworkAnimation::refresh() {
    calcFrame();
    matrix->setDisplayData(&frame);
    matrix->sendData();


}

void FireworkAnimation::calcFrame() {

    if (timeSinceLastFirework >= TIME_BETWEEN_FIREWORKS) {
        createNewFirework();
    }
    timeSinceLastFirework++;

    blankFrame();

    for (detailsFirework::Firework* & i : firework) {
        i->calcFrame(&frame);
    }


}

void FireworkAnimation::createNewFirework() {
    // Get "random" location (not to near to previous firework)
    uint8_t postion = randomInt(0, NUMBER_POSITIONS);
    while (lastFireWorkPostion + MIN_SPACE_BETWEEN_POSTIONS >= postion &&
           lastFireWorkPostion - MIN_SPACE_BETWEEN_POSTIONS <= postion) {
        postion = randomInt(0, NUMBER_POSITIONS);
    }

    addNewFirework(postions[postion], randomInt(FIREWORK_EXPLODE_Y_MIN, FIREWORK_EXPLODE_Y_MAX), randomColor[fireworkColor]);

    timeSinceLastFirework = 0;
    lastFireWorkPostion = postion;
    fireworkColor = (fireworkColor + 1) % NUMBER_FIREWORK_COLORS;

}

void FireworkAnimation::addNewFirework(int8_t explodePosX, int8_t explodePosY, Color *color) {
    for (detailsFirework::Firework* & i : firework) {
        if (i->dead) {
            i->start(explodePosX, explodePosY, color);
            break;
        }
    }
}

void FireworkAnimation::blankFrame() {
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int j = 0; j < MATRIX_LENGTH; j++) {
            frame[i][j] = colorBlank123;
        }
    }
}

void FireworkAnimation::button1ISR(bool state) {

}

void FireworkAnimation::button2ISR(bool state) {

}

void FireworkAnimation::restart() {

}



