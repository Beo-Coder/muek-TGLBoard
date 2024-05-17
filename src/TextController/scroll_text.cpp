//
// Created by leo on 06.03.24.
//

#include "scroll_text.h"

ScrollText::ScrollText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) : TextController(
        matrixOutput, frame) {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;

    leftShift = true;

    refreshSpeed = 120;


}

void ScrollText::createIDTextArray(String *text) {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;
    for (unsigned int i = 0; i < text->length(); i++) {
        char charAtIndex = text->charAt(i);
        if (charAtIndex == '%') {
            charAtIndex = text->charAt(i + 1);
            int index = specialChars.indexOf(charAtIndex);
            if (index != -1) {
                idTextArray[idTextArraySize] = index + normalChars.length();
                i++;
            }

        } else {
            int index = normalChars.indexOf(charAtIndex);
            if (index != -1) {
                idTextArray[idTextArraySize] = index;
            }
        }
        idTextArraySize++;

        // Add spaces between letters
        for (int j = 0; j < spaceBetweenLetters; j++) {
            idTextArray[idTextArraySize] = SINGLE_SPACE_INDEX;
            idTextArraySize++;
        }
        setMode(leftShift);

    }

}


void ScrollText::shiftToLeftSide() {
    for (int i = 0; i < MATRIX_LENGTH; i++) {
        shiftTextLeft();
        loadNewBitsLeftShift();
    }
}


void ScrollText::shiftTextLeft() {

    for (int row = 0; row < 8; row++) {

        for (int column = 0; column < MATRIX_LENGTH - 1; column++) {
            (*frame)[row][column] = (*frame)[row][column + 1];

        }
    }

}

void ScrollText::loadNewBitsLeftShift(bool loadFrame) {

    const uint8_t *letter = Letter[idTextArray[matrixBitOffset / Letter[idTextArray[idTextArrayIndex]][8] +
                                               idTextArrayIndex]];
    if(loadFrame){
        for (int row = 0; row < 8; row++) {


            if (letter[row] >> (letter[8] - 1 - matrixBitOffset) % (letter[8]) & 0x01) {
                (*frame)[row][MATRIX_LENGTH - 1] = *textColor;

            } else {
                (*frame)[row][MATRIX_LENGTH - 1] = *backgroundColor;

            }

        }
    }


    matrixBitOffset++;
    if (matrixBitOffset % (letter[8]) == 0) {
        matrixBitOffset = 0;
        idTextArrayIndex++;
    }

    idTextArrayIndex = idTextArrayIndex % idTextArraySize;

}

void ScrollText::shiftTextRight() {
    for (int row = 0; row < 8; row++) {

        for (int column = MATRIX_LENGTH - 1; column > 0; column--) {
            (*frame)[row][column] = (*frame)[row][column - 1];

        }
    }

}

void ScrollText::loadNewBitsRightShift(bool loadFrame) {
    const uint8_t *letter = Letter[idTextArray[matrixBitOffset / Letter[idTextArray[idTextArrayIndex]][8] +
                                               idTextArrayIndex]];

    if (matrixBitOffset >= 0 && loadFrame) {
        for (int row = 0; row < 8; row++) {


            if (letter[row] >> (matrixBitOffset) % (letter[8]) & 0x01) {
                (*frame)[row][0] = *textColor;

            } else {
                (*frame)[row][0] = *backgroundColor;

            }

        }
    }


    matrixBitOffset++;
    if (matrixBitOffset % (letter[8]) == 0) {
        matrixBitOffset = 0;

        if (idTextArrayIndex == 0) {
            idTextArrayIndex = idTextArraySize - 1;
        } else {
            idTextArrayIndex--;
        }


    }


}


void ScrollText::createAndLoadFrame() {
    if (leftShift) {
        shiftTextLeft();
        loadNewBitsLeftShift();
    } else {
        shiftTextRight();
        loadNewBitsRightShift();
    }
    matrix->setDisplayData(frame);


}


void ScrollText::setMode(bool leftShift) {
    this->leftShift = leftShift;
    if (leftShift) {
        idTextArrayIndex = 0;
    } else {
        idTextArrayIndex = idTextArraySize - 1;
    }

}

void ScrollText::setSpaceBetweenLetters(uint8_t space) {
    spaceBetweenLetters = space;
}


void ScrollText::refresh() {

    createAndLoadFrame();
    matrix->sendData();
}


void ScrollText::restart() {
    clearFrame();

    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;

}















