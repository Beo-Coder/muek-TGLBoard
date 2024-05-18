//
// Created by leo on 01.05.24.
//

#include "firework.h"
#include "beo_common.h"
#include "pixel.h"

details_firework::Firework::Firework() {
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



void details_firework::Firework::start(int8_t posX, int8_t posY, Color *color) {
    lifeTime = 0;
    dead = false;
    arrived = false;
    exploded = false;

    this->startPosX = posX;
    this->startPosY = 0;

    pixelColor = *color;
    pixelColor.setBrightness(FIREWORK_EXPLOSION_BRIGHTNESS);

    // Configure each pixel
    for (int i = 0; i < PIXEL_PER_FIREWORK; i++) {
        pixel[i]->posX = posX;
        pixel[i]->posY = posY;

        // This could certainly be improved
        switch (i % 4) {
            case 0:
                pixel[i]->dirX = float(beo::randomInt(0, FIREWORK_SPEED_VALUE_X + 1));
                pixel[i]->dirY = float(beo::randomInt(0, FIREWORK_SPEED_VALUE_Y + 1));
                break;
            case 1:
                pixel[i]->dirX = float(beo::randomInt(-FIREWORK_SPEED_VALUE_X, 0));
                pixel[i]->dirY = float(beo::randomInt(0, FIREWORK_SPEED_VALUE_Y + 1));
                break;
            case 2:
                pixel[i]->dirX = float(beo::randomInt(0, FIREWORK_SPEED_VALUE_X + 1));
                pixel[i]->dirY = float(beo::randomInt(-FIREWORK_SPEED_VALUE_Y, 0));
                break;
            case 3:
                pixel[i]->dirX = float(beo::randomInt(-FIREWORK_SPEED_VALUE_X, 0));
                pixel[i]->dirY = float(beo::randomInt(-FIREWORK_SPEED_VALUE_Y, 0));
                break;
        }

        pixel[i]->color = &pixelColor;


    }

}

void details_firework::Firework::calcFrame(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {
    if (!exploded) {
        calcFireworkTrail(display);
    } else {
        calcFireworkExplosion(display);
    }

}

void details_firework::Firework::calcFireworkTrail(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {


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
            (*display)[MATRIX_HEIGHT - (startPosY-i) - 1][startPosX] = *trailColor;
        }
    }


    (*display)[MATRIX_HEIGHT - trailPosY - 1][startPosX] = *trailColor;

    startPosY++;



}

void details_firework::Firework::calcFireworkExplosion(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]) {

    if (lifeTime < FIREWORK_LIFE_TIME) {
        for (Pixel* & i : pixel) {
            int8_t posX = i->posX;
            int8_t posY = i->posY;

            if(lifeTime > 0){
                i->color->setBrightness(FIREWORK_AFTER_EXPLOSION_BRIGHTNESS-(lifeTime*FIREWORK_AFTER_EXPLOSION_BRIGHTNESS_SINKRATE-1));
                //i->color->setBrightness(1);
            }

            i->posX += (i->dirX * (1 - (float(lifeTime) / FIREWORK_DECELERATION_VALUE_X))) /
                       FIREWORK_SPEED_VALUE_X2;
            i->posY += (i->dirY * (1 - (float(lifeTime) / FIREWORK_DECELERATION_VALUE_Y))) /
                       FIREWORK_SPEED_VALUE_Y2 - FIREWORK_SINK_RATE;

            // Only add to frame, when pixel is inside frame
            if (posX >= 0 && posX < MATRIX_LENGTH && posY >= 0 && posY < MATRIX_HEIGHT) {
                (*display)[MATRIX_HEIGHT - posY - 1][posX] = *(i->color);
            }

        }


        lifeTime++;
    }else{
        dead = true;
    }

}
