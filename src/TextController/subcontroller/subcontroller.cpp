//
// Created by leo on 17.05.24.
//

#include "subcontroller.h"
#include "../charsets/charset.h"


details_text_controller::Subcontroller::Subcontroller(uint16_t idArrayOffset, uint16_t yPos, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t *idTextArray, const Charset *charset, Color *textColor, Color *backgroundColor) {
    this->idArrayOffset = idArrayOffset;
    this->yPos = yPos;
    this->frame = frame;
    this->idTextArray = idTextArray;
    this->charset = charset;
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;
    idArraySize = 0;
    idArrayIndex = 0;
    idArrayBitOffset = 0;


}

void details_text_controller::Subcontroller::setArraySize(uint16_t size) {
    idArrayBitOffset = 0;
    idArrayIndex = 0;
    idArraySize = size;

}


void details_text_controller::Subcontroller::shiftTextLeft() {
    for(int i=0; i<charset->charHeight; i++){
        for(int j=0; j<MATRIX_LENGTH-1; j++){
            (*frame)[i+yPos][j] = (*frame)[i+yPos][j+1];
        }
    }
}

void details_text_controller::Subcontroller::shiftTextRight() {
    for(int i=0; i<charset->charHeight; i++){
        for(int j=MATRIX_LENGTH-1; j>0; j--){
            (*frame)[i+yPos][j] = (*frame)[i+yPos][j-1];
        }
    }

}

void details_text_controller::Subcontroller::loadNewDataLeftShift(bool loadFrame) {

    const uint8_t *letter = charset->chars[idTextArray[(idArrayBitOffset / charset->chars[idTextArray[idArrayIndex+idArrayOffset]][charset->charHeight] + idArrayIndex)+idArrayOffset]];
    if(loadFrame){
        for (int row = 0; row < charset->charHeight; row++) {


            if (letter[row] >> (letter[charset->charHeight] - 1 - idArrayBitOffset) % (letter[charset->charHeight]) & 0x01) {
                (*frame)[row+yPos][MATRIX_LENGTH - 1] = *textColor;

            } else {
                (*frame)[row+yPos][MATRIX_LENGTH - 1] = *backgroundColor;

            }

        }
    }


    idArrayBitOffset++;
    if (idArrayBitOffset % (letter[charset->charHeight]) == 0) {
        idArrayBitOffset = 0;
        idArrayIndex++;
    }

    idArrayIndex = idArrayIndex % idArraySize;

}

void details_text_controller::Subcontroller::loadNewDataRightShift(bool loadFrame) {
    const uint8_t *letter = charset->chars[idTextArray[(idArrayBitOffset / charset->chars[idTextArray[idArrayIndex+idArrayOffset]][charset->charHeight] + idArrayIndex)+idArrayOffset]];

    if (idArrayBitOffset >= 0 && loadFrame) {
        for (int row = 0; row < charset->charHeight; row++) {


            if (letter[row] >> (idArrayBitOffset) % (letter[charset->charHeight]) & 0x01) {
                (*frame)[row+yPos][0] = *textColor;

            } else {
                (*frame)[row+yPos][0] = *backgroundColor;

            }

        }
    }


    idArrayBitOffset++;
    if (idArrayBitOffset % (letter[charset->charHeight]) == 0) {
        idArrayBitOffset = 0;

        if (idArrayIndex == 0) {
            idArrayIndex = idArraySize - 1;
        } else {
            idArrayIndex--;
        }


    }

}

void details_text_controller::Subcontroller::setIdArrayIndex(uint16_t idArrayIndex) {
    this->idArrayIndex = idArrayIndex;

}

void details_text_controller::Subcontroller::setColor(Color *textColor, Color *backgroundColor) {
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;

}


