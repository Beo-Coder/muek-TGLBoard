//
// Created by leo on 06.03.24.
//

#include "scroll_text.h"

ScrollText::ScrollText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) : display_program(matrixOutput, frame) {
    // this->matrix = matrixOutput;
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;

    refreshSpeed = 120;

    scroll = true;
    needScrolling = false;

}

void ScrollText::createIDTextArray(String *text) {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;
    for (unsigned int i = 0; i < text->length(); i++) {
        char charAtIndex = text->charAt(i);
        if(charAtIndex == '%'){
            charAtIndex = text->charAt(i+1);
            int index = specialChars.indexOf(charAtIndex);
            if(index != -1){
                idTextArray[idTextArraySize] = index + normalChars.length();
                i++;
            }

        }else{
            int index = normalChars.indexOf(charAtIndex);
            if(index != -1){
                idTextArray[idTextArraySize] = index;
            }
        }
        idTextArraySize++;
    }

}

void ScrollText::setText(String *text, bool scroll) {
    createIDTextArray(text);
    this->scroll = scroll;
    if(!scroll){
        setStaticText();
    }


}

void ScrollText::setColor(Color *textColor, Color *backgroundColor) {
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;

}




void ScrollText::shiftText() {


    const uint8_t *letter = Letter[idTextArray[matrixBitOffset / ( Letter[idTextArray[idTextArrayIndex]][8] + SPACE_BETWEEN_LETTERS) + idTextArrayIndex]];
    for (int row = 0; row < 8; row++) {

        for (int column = 0; column < MATRIX_LENGTH-1; column++) {
            (*frame)[row][column] = (*frame)[row][column + 1];

        }


        if (letter[row] >> (((letter[8] - 1 + SPACE_BETWEEN_LETTERS - matrixBitOffset) %
                             (letter[8] + SPACE_BETWEEN_LETTERS))) & 0x01) {
            (*frame)[row][MATRIX_LENGTH-1] = *textColor;

        } else {
            (*frame)[row][MATRIX_LENGTH-1] = *backgroundColor;

        }

    }

    matrixBitOffset++;
    if (matrixBitOffset % (letter[8] + SPACE_BETWEEN_LETTERS) == 0) {
        matrixBitOffset = 0;
        idTextArrayIndex++;
    }

    idTextArrayIndex = idTextArrayIndex % idTextArraySize;



}

void ScrollText::setStaticText() {
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

}




void ScrollText::shiftToLeftSide() {

    staticTextTime = 0;
    for(int i=0; i<MATRIX_LENGTH+1; i++){
        shiftText();
    }

}


void ScrollText::staticText() {
    if(needScrolling){
        staticTextTime++;

        // Wait until wait time is over, than shift to the left
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
            stopScrolling = false;
        }
    }


}



void ScrollText::refresh() {
    if(scroll){
        shiftText();
    }else{
        staticText();
    }

    matrix->addToFrameBuffer(frame);
    matrix->sendData();

}

void ScrollText::restart() {
    clearFrame();

    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;

    scroll = true;
    needScrolling = false;


}

void ScrollText::button1ISR(bool state) {

}

void ScrollText::button2ISR(bool state) {

}










