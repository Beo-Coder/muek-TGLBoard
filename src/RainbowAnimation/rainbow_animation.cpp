//
// Created by leo on 25.05.24.
//

#include "rainbow_animation.h"




namespace details_rainbow_animation{
    const uint8_t colorCount = 6;
    const Color *rainbowColors[] = {&colorPurple, &colorBlue,&colorCyan, &colorGreen, &colorYellow, &colorRed};

}

RainbowAnimation::RainbowAnimation(MatrixOutput *ledMatrix, Color (*frame)[8][16]) : DisplayProgram(ledMatrix, frame) {
    refreshSpeed = 120;

    currentColor = 0;
}


void RainbowAnimation::calcFrame() {
    uint8_t offsetColor = 0;

    for(int i=0; i<MATRIX_HEIGHT; i++){
        offsetColor = (MATRIX_HEIGHT/2)-(i/2);
        for(int j=0; j<MATRIX_LENGTH; j++){
            (*frame)[i][j] = *details_rainbow_animation::rainbowColors[(j+currentColor+offsetColor)%details_rainbow_animation::colorCount];

        }
    }
    currentColor = (currentColor+1)%details_rainbow_animation::colorCount;

}


void RainbowAnimation::restart() {
    currentColor = 0;

}

void RainbowAnimation::refresh() {
    calcFrame();
    matrix->setDisplayData(frame);
    matrix->sendData();

}

void RainbowAnimation::button1ISR(bool data) {

}

void RainbowAnimation::button2ISR(bool data) {

}


