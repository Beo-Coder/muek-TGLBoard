//
// © 2024 Leonhard Baschang
//

#include "fixed_animation.h"


FixedAnimation::FixedAnimation(MatrixOutput *ledMatrix, Color (*frame)[8][16]) : DisplayProgram(ledMatrix, frame) {
    refreshSpeed = 150;
    frameIndex = 0;
    animationIndex = 0;

    currenAnimation = animations[animationIndex];
    refreshSpeed = currenAnimation->speed;

}

void FixedAnimation::restart() {
    frameIndex = 0;
    clearFrame();

}

void FixedAnimation::refresh() {


    for(int i=0; i<MATRIX_HEIGHT; i++){
        for(int j=0; j<MATRIX_LENGTH; j++){
            (*frame)[i][j] = *currenAnimation->colorIndex[(*(*currenAnimation->frames)[frameIndex])[i][j]];
        }
    }
    matrix->setDisplayData(frame);
    matrix->sendData();
    frameIndex = (frameIndex + 1)%currenAnimation->length;



}

void FixedAnimation::button1ISR(bool data) {


}

void FixedAnimation::button2ISR(bool data) {

}
