//
// Created by leo on 25.05.24.
//

#include "rainbow_animation.h"



RainbowAnimation::RainbowAnimation(MatrixOutput *ledMatrix, Color (*frame)[8][16]) : DisplayProgram(ledMatrix, frame) {
    refreshSpeed = details_rainbow_animation::REFRESH_SPEED;

    currentColor = 0;
    mode = fixed;
}


void RainbowAnimation::calcFrame() {
    uint8_t offsetColor = 0;

    for(int i=0; i<MATRIX_HEIGHT; i++){
        offsetColor = (MATRIX_HEIGHT/2)-(i/2);



        for(int j=0; j<MATRIX_LENGTH; j++){
            switch(mode){
                case fixed:
                    (*frame)[i][j] = *details_rainbow_animation::rainbowColors[(j+currentColor+offsetColor)%details_rainbow_animation::colorCount];
                    break;
                case smooth:
                    float colorData[3];
                    for(int k=0; k<3; k++){

                        colorData[k] = (float) (NORMAL_BRIGHTNESS*details_rainbow_animation::BRIGHTNESS_FACTOR * sin((2*PI/MATRIX_LENGTH)*((j+offsetColor+currentColor)%MATRIX_LENGTH-(MATRIX_LENGTH*(k/3.0)))));
                        if(colorData[k] < 0){
                            colorData[k] = 0;
                        }
                    }

                    pixelColor.setRed(colorData[0]);
                    pixelColor.setGreen(colorData[1]);
                    pixelColor.setBlue(colorData[2]);

                    (*frame)[i][j] = pixelColor;
                    break;
            }
        }
    }
    currentColor = (currentColor+1)%numberColorValues;

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

void RainbowAnimation::setMode(RainbowMode mode) {
    this->mode = mode;
    switch(mode){
        case fixed:
            numberColorValues = details_rainbow_animation::colorCount;
            break;
        case smooth:
            numberColorValues = MATRIX_LENGTH;
            break;
        default:
            this->mode = fixed;
            numberColorValues = details_rainbow_animation::colorCount;
            break;
    }

}


