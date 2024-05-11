//
// Created by leo on 06.03.24.
//

#include "scroll_text.h"

ScrollText::ScrollText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) : TextController(matrixOutput, frame) {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;

    refreshSpeed = 120;


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



void ScrollText::shiftToLeftSide() {
    for(int i=0; i<MATRIX_LENGTH+1; i++){
        shiftText();
    }
}




void ScrollText::refresh() {
    shiftText();

    matrix->setDisplayData(frame);
    matrix->sendData();
}

void ScrollText::restart() {
    clearFrame();

    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;

}











