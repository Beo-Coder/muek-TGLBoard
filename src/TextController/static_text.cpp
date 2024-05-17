//
// Created by leo on 11.05.24.
//

#include "static_text.h"

StaticText::StaticText(MatrixOutput *matrixOutput, Color (*frame)[8][16]) : ScrollText(matrixOutput, frame) {

    needScrolling = false;
    staticTextTime = 0;
    state = 0;

    refreshSpeed = 120;

}


void StaticText::initText() {
    uint16_t textLength = 0;
    for (int i = 0; i < idTextArraySize; i++) {
        textLength += (Letter[idTextArray[i]])[8];
        // textLength += spaceBetweenLetters;

    }
    // textLength -= spaceBetweenLetters;



    if (textLength > MATRIX_LENGTH) {
        needScrolling = true;
        shiftToLeftSide();

        for (int i = 0; i <= NUMBER_FREE_PIXELS_ADDED_STATIC_TEXT; i++) {
            idTextArray[idTextArraySize] = SINGLE_SPACE_INDEX;
            idTextArraySize++;
        }
    } else {
        needScrolling = false;

        // fill it up with blank spaces
        for (int i = textLength; i < MATRIX_LENGTH; i++) {
            idTextArray[idTextArraySize] = SINGLE_SPACE_INDEX;
            idTextArraySize++;
        }

        shiftToLeftSide();
    }
    staticTextTime = 0;


}


void StaticText::refreshText() {

    if (needScrolling) {
        staticTextTime++;


        // Wait until wait time is over, then shift to the left
        if (staticTextTime >= STATIC_TEXT_WAIT_TIME_START && (state == 0 || state == 1)) {
            shiftTextLeft();
            loadNewBitsLeftShift();
            state = 1;

        }

        // if shifted all the way, wait and set the indices to right shift operation on the same postion
        // (could be done smarter)
        if (idTextArrayIndex == idTextArraySize - 1 && matrixBitOffset == 0 && staticTextTime != 0 && state == 1) {
            staticTextTime = 0;
            state = 2;


            idTextArrayIndex = idTextArraySize - 1;
            matrixBitOffset = 0;


            for (int j = 0; j < MATRIX_LENGTH + 1; j++) {
                loadNewBitsRightShift(false);
            }


        }


        // "Reset" the scroll text to the start (is over the right shift, because of timing constraints)
        if (idTextArrayIndex == 0 && matrixBitOffset == Letter[idTextArray[idTextArrayIndex]][8] - 1 && state == 3) {
            staticTextTime = 0;
            state = 0;
            matrixBitOffset = 0;
            idTextArrayIndex = 0;
            shiftToLeftSide();

        }

        // Shift right, back to the "start"
        if (staticTextTime >= STATIC_TEXT_WAIT_TIME_END && (state == 2 || state == 3)) {
            shiftTextRight();
            loadNewBitsRightShift();
            state = 3;

        }


    }

}


void StaticText::setText(String *text) {
    TextController::setText(text);
    initText();
}


void StaticText::createAndLoadFrame() {
    refreshText();

    matrix->setDisplayData(frame);
}

void StaticText::refresh() {
    createAndLoadFrame();
    matrix->sendData();

}

void StaticText::restart() {
    ScrollText::restart();
    needScrolling = false;
    staticTextTime = 0;
    state = 0;


}






