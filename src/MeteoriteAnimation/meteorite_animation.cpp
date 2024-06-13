//
// Created by leo on 25.05.24.
//

#include "meteorite_animation.h"
#include "beo_common.h"



MeteoriteAnimation::MeteoriteAnimation(MatrixOutput *ledMatrix, Color (*frame)[8][16]) : DisplayProgram(ledMatrix,
                                                                                                        frame) {
    refreshSpeed = 70;


    counterNewTrail = 0;

    for(int i=0; i<details_meteorite_animation::MAX_NUMBER_METEORITE_TRAILS; i++){
        trails[i].length = 0;
        trails[i].posY = 0;
        trails[i].posX = 0;
        trails[i].alive = false;

    }


}


void MeteoriteAnimation::newTrail() {

    for(int i=0; i<details_meteorite_animation::MAX_NUMBER_METEORITE_TRAILS; i++){
        if(!trails[i].alive){
            trails[i].length = beo::randomInt(3,8);
            trails[i].posY = getYPos();
            trails[i].posX = 0;
            trails[i].alive = true;
            break;
        }
    }
}

void MeteoriteAnimation::restart() {
    counterNewTrail = 0;

    for(int i=0; i<details_meteorite_animation::MAX_NUMBER_METEORITE_TRAILS; i++){
        trails[i].length = 0;
        trails[i].posY = 0;
        trails[i].posX = 0;
        trails[i].alive = false;

    }

}

void MeteoriteAnimation::refresh() {
    clearFrame();
    for(int i=0; i<details_meteorite_animation::MAX_NUMBER_METEORITE_TRAILS; i++){
        if(trails[i].alive){
            for(int j=0; j<trails[i].length; j++){

                uint8_t xPos = trails[i].posX-j;
                if(xPos >=0 && xPos < MATRIX_LENGTH){
                    (*frame)[trails[i].posY][xPos] = *getColor(xPos);
                }
            }
            trails[i].posX++;

        }

        if(trails[i].posX - trails[i].length > MATRIX_LENGTH){
            trails[i].alive = false;
        }
    }



    if(counterNewTrail > beo::randomInt(details_meteorite_animation::MIN_TIME_NEW_TRAIL, details_meteorite_animation::MAX_TIME_NEW_TRAIL)){
        newTrail();
        counterNewTrail = 0;
    }
    counterNewTrail++;

    matrix->setDisplayData(frame);
    matrix->sendData();

}






void MeteoriteAnimation::button2ISR(bool data) {

}

void MeteoriteAnimation::button1ISR(bool data) {

}

uint8_t MeteoriteAnimation::getYPos() {

    uint8_t possiblePositions[MATRIX_HEIGHT];
    uint8_t possiblePositionsCount = 0;

    uint8_t impossiblePositions[MATRIX_HEIGHT];
    uint8_t impossiblePositionsCount = 0;


    for(int i=0; i<details_meteorite_animation::MAX_NUMBER_METEORITE_TRAILS; i++){
        if(trails[i].alive){
            if(trails[i].posX - trails[i].length < details_meteorite_animation::MIN_DISTANCE_TRAILS){
                impossiblePositions[impossiblePositionsCount] = trails[i].posY;
                impossiblePositionsCount++;
            }
        }
    }

    for(int i=0; i<MATRIX_HEIGHT; i++){
        bool impossible = false;
        for(int j=0; j<impossiblePositionsCount; j++){
            if(i == impossiblePositions[j]){
                impossible = true;
                break;
            }
        }
        if(!impossible){
            possiblePositions[possiblePositionsCount] = i;
            possiblePositionsCount++;
        }
    }
    if(possiblePositionsCount == 0){
        return 0;
    }

    return possiblePositions[beo::randomInt(0,possiblePositionsCount)];

}

Color *MeteoriteAnimation::getColor(uint8_t posX) {

    float colorData[3];
    for(int i=0; i<3; i++){
        colorData[i] = (float) (NORMAL_BRIGHTNESS*details_meteorite_animation::BRIGHTNESS_FACTOR * sin((2*PI/MATRIX_LENGTH)*(posX+(MATRIX_LENGTH*1.0/6.0)-(MATRIX_LENGTH*(i/3.0)))));
        if(colorData[i] < 0){
            colorData[i] = 0;
        }
    }

    pixelColor.setRed(colorData[0]);
    pixelColor.setGreen(colorData[1]);
    pixelColor.setBlue(colorData[2]);


    return &pixelColor;
}
