//
// Created by leo on 17.05.24.
//

#include "static_subcontroller.h"
#include "../charsets/charset.h"

details_text_controller::StaticSubcontroller::StaticSubcontroller(uint16_t idArrayOffset, uint16_t yPos,
                                                                  Color (*frame)[8][16], uint8_t *idTextArray,
                                                                  const Charset *charset, const Color *textColor,
                                                                  const Color *backgroundColor) : Subcontroller(idArrayOffset,
                                                                                                          yPos, frame,
                                                                                                          idTextArray,
                                                                                                          charset,
                                                                                                          textColor,
                                                                                                          backgroundColor) {


    state = 0;
    needScrolling = false;
    staticTextTime = 0;
}


void details_text_controller::StaticSubcontroller::initText() {
    uint16_t textLength = 0;
    state = 0;
    needScrolling = false;
    for(int i=0; i<idArraySize; i++){
        textLength += (charset->chars[idTextArray[i+idArrayOffset]])[charset->charHeight];
    }

    if(textLength > MATRIX_LENGTH){
        needScrolling = true;
        shiftAllTheWayLeft();

        for(int i=0; i<=NUMBER_FREE_SPACES; i++){
            idTextArray[idArraySize+idArrayOffset] = *charset->singleSpaceIndex;
            idArraySize++;

        }
    }else{
        needScrolling = false;

        // fill it up with blank spaces
        for (int i = textLength; i < MATRIX_LENGTH; i++) {
            idTextArray[idArraySize+idArrayOffset] = *charset->singleSpaceIndex;
            idArraySize++;
        }

        shiftAllTheWayLeft();
    }
    staticTextTime = 0;


}

void details_text_controller::StaticSubcontroller::shiftAllTheWayLeft() {
    for(int i=0; i<MATRIX_LENGTH; i++){
        shiftTextLeft();
        loadNewDataLeftShift();
    }

}

void details_text_controller::StaticSubcontroller::shiftAllTheWayRight() {
    for(int i=0; i<MATRIX_LENGTH; i++){
        shiftTextRight();
        loadNewDataRightShift();
    }

}

void details_text_controller::StaticSubcontroller::refreshText() {
    if (needScrolling) {

        staticTextTime++;


        // Wait until wait time is over, then shift to the left
        if (staticTextTime >= WAIT_TIME_BEGIN && (state == 0 || state == 1)) {
            shiftTextLeft();
            loadNewDataLeftShift();
            state = 1;

        }

        // if shifted all the way, wait and set the indices to right shift operation on the same postion
        // (could be done smarter)
        if (idArrayIndex == idArraySize - 1 && idArrayBitOffset == 0 && staticTextTime != 0 && state == 1) {
            staticTextTime = 0;
            state = 2;


            idArrayIndex = idArraySize - 1;
            idArrayBitOffset = 0;


            for (int j = 0; j < MATRIX_LENGTH + 1; j++) {
                loadNewDataRightShift(false);
            }


        }


        // "Reset" the scroll text to the start (is over the right shift, because of timing constraints)
        if (idArrayIndex == 0 && idArrayBitOffset == charset->chars[idTextArray[idArrayIndex+idArrayOffset]][charset->charHeight] - 1 && state == 3) {
            staticTextTime = 0;
            state = 0;
            idArrayBitOffset = 0;
            idArrayIndex = 0;
            shiftAllTheWayLeft();

        }

        // Shift right, back to the "start"
        if (staticTextTime >= WAIT_TIME_END && (state == 2 || state == 3)) {
            shiftTextRight();
            loadNewDataRightShift();
            state = 3;

        }


    }


}
