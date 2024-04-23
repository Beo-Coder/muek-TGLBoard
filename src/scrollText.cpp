//
// Created by leo on 06.03.24.
//

#include "scrollText.h"

scrollText::scrollText(MatrixOutput *displayController) {
    this->displayController = displayController;
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;

}

void scrollText::createIDTextArray(String *text) {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    matrixBitOffset = 0;
    for (unsigned int i = 0; i < text->length(); i++) {
        idTextArray[idTextArraySize] = letterSeries.indexOf(text->charAt(i));
        idTextArraySize++;
    }

}

void scrollText::setText(String *text) {
    createIDTextArray(text);


}

void scrollText::setColor(Color *textColor, Color *backgroundColor) {
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;

}

void scrollText::shiftText() {

    const uint8_t *letter = Letter[idTextArray[matrixBitOffset / (5 + SPACE_BETWEEN_LETTERS) + idTextArrayIndex]];
    for (int row = 0; row < 8; row++) {

        for (int column = 0; column < 15; column++) {
            displayData[row][column] = displayData[row][column + 1];

        }


        if (letter[row] >> (((letter[8] - 1 + SPACE_BETWEEN_LETTERS - matrixBitOffset) %
                             (letter[8] + SPACE_BETWEEN_LETTERS))) & 0x01) {
            displayData[row][15] = *textColor;

        } else {
            displayData[row][15] = *backgroundColor;

        }

    }

    matrixBitOffset++;
    if (matrixBitOffset % (letter[8] + SPACE_BETWEEN_LETTERS) == 0) {
        matrixBitOffset = 0;
        idTextArrayIndex++;
    }
    idTextArrayIndex = idTextArrayIndex % idTextArraySize;

    displayController->addToFrameBuffer(&displayData);

}


