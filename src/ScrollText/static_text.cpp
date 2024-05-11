//
// Created by leo on 11.05.24.
//

#include "static_text.h"

StaticText::StaticText(MatrixOutput *matrixOutput, Color (*frame)[8][16]) : ScrollText(matrixOutput, frame) {

    needScrolling  = false;
    staticTextTime = 0;
    stopScrolling = false;

    refreshSpeed = 120;

}


void StaticText::initText() {
    uint16_t textLength = 0;
    for(int i=0; i<idTextArraySize; i++){
        textLength += (Letter[idTextArray[i]])[8];
        textLength += SPACE_BETWEEN_LETTERS;

    }
    textLength -= SPACE_BETWEEN_LETTERS;



    if(textLength > MATRIX_LENGTH){
        needScrolling = true;
        shiftToLeftSide();

        for(int i=0; i<NUMBER_FREE_PIXELS_ADDED_STATIC_TEXT; i++){
            idTextArray[idTextArraySize] = SINGLE_SPACE_INDEX;
            idTextArraySize++;
        }
    }else{
        needScrolling = false;

        // fill it up with blank spaces
        for(int i=textLength; i<MATRIX_LENGTH; i+=2){
            idTextArray[idTextArraySize] = SINGLE_SPACE_INDEX;
            idTextArraySize++;
        }

        shiftToLeftSide();
    }
    staticTextTime = 0;


}


void StaticText::refreshText() {

    if(needScrolling){
        staticTextTime++;

        // Wait until wait time is over, then shift to the left
        if(staticTextTime >= STATIC_TEXT_WAIT_TIME_START && idTextArrayIndex != 0 && !stopScrolling){
            shiftText();
        }

        // if shifted all the way, wait
        if(idTextArrayIndex == 0 && staticTextTime != 0 && !stopScrolling){
            staticTextTime = 0;
            stopScrolling = true;
        }

        // is shifted all the way and wait time is over "reset"
        if(staticTextTime >= STATIC_TEXT_WAIT_TIME_END && stopScrolling){
            clearFrame();
            shiftToLeftSide();
            staticTextTime = 0;
            stopScrolling = false;
        }
    }

}




void StaticText::setText(String *text, bool clearDisplay) {
    TextController::setText(text, clearDisplay);
    initText();
}


void StaticText::refresh() {
    refreshText();

    matrix->setDisplayData(frame);
    matrix->sendData();

}

void StaticText::restart() {
    ScrollText::restart();
    needScrolling = false;
    staticTextTime = 0;
    stopScrolling = false;


}




