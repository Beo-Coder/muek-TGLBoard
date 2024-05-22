//
// Created by leo on 14.05.24.
//

#include "tiny_text.h"
#include "charsets/charset.h"
#include "subcontroller/static_subcontroller.h"


TinyText::TinyText(MatrixOutput *matrixOutput, Color (*frame)[8][16]) : TextController(matrixOutput, frame) {
    refreshSpeed = 120;

    *upperTextArraySize = 0;
    lowerTextArraySize = 0;
    lowerTextColor = &colorGreen;



    upperController = new details_text_controller::StaticSubcontroller(0, 0, frame, idTextArray, &tinyLetters,
                                                                       textColor, backgroundColor);
    lowerController = new details_text_controller::StaticSubcontroller(MAX_TEXT_LENGTH / 2, details_tiny_text::SUBMATRIX_HEIGHT, frame,
                                                                       idTextArray, &tinyLetters, lowerTextColor,
                                                                       backgroundColor);


}



void TinyText::createIDTextArray(std::string *text) {
    createIDTextArray(text, 0);

}


void TinyText::createIDTextArray(std::string *text, uint8_t startIndex) {
    uint16_t *localIdTextArraySize = upperTextArraySize;
    uint16_t bitOffset = 0;
    if(startIndex == 0){
        *upperTextArraySize = 0;
    }else{
        lowerTextArraySize = 0;
        localIdTextArraySize = &lowerTextArraySize;
        bitOffset = MAX_TEXT_LENGTH/2;
    }






    for (unsigned int i = 0; i < text->length(); i++) {
        char charAtIndex = text->at(i);
        if (charAtIndex == '%') {
            charAtIndex = text->at(i + 1);
            unsigned int index = details_letters_tiny::tinySpecialChars.find(charAtIndex);

            if (index == details_letters_tiny::breakCharSpecialIndex) {
                localIdTextArraySize = &lowerTextArraySize;
                bitOffset = MAX_TEXT_LENGTH/2;
                i++;
                continue;

            }

            if (index != std::string::npos) {
                idTextArray[(*localIdTextArraySize)+bitOffset] = index + details_letters_tiny::tinyNormalChars.length();
                i++;
            }

        } else {
            unsigned int index = details_letters_tiny::tinyNormalChars.find(charAtIndex);
            if (index != std::string::npos) {
                idTextArray[(*localIdTextArraySize)+bitOffset] = index;
            }
        }

        (*localIdTextArraySize)++;

        // Add spaces between letters
        for (int j = 0; j < details_tiny_text::SPACE_BETWEEN_LETTERS; j++) {
            idTextArray[(*localIdTextArraySize)+bitOffset] = details_letters_tiny::SINGLE_SPACE_INDEX;
            (*localIdTextArraySize)++;
        }


    }
    if(startIndex == 0){
        upperController->setArraySize(*upperTextArraySize);
        upperController->initText();
    }else{
        lowerController->setArraySize(lowerTextArraySize);
        lowerController->initText();
    }



}





void TinyText::setText(std::string *text) {
    createIDTextArray(text);

    upperController->setArraySize(*upperTextArraySize);
    lowerController->setArraySize(lowerTextArraySize);

    upperController->initText();
    lowerController->initText();

}


void TinyText::refresh() {
    createAndLoadFrame();
    matrix->sendData();


}

void TinyText::restart() {
    *upperTextArraySize = 0;
    lowerTextArraySize = 0;
    idTextArrayIndex = 0;

}

void TinyText::createAndLoadFrame() {
    upperController->refreshText();
    lowerController->refreshText();
    matrix->setDisplayData(frame);

}

void TinyText::setColor(Color *upperTextColor, Color *lowerTextColor, Color *backgroundColor) {
    textColor = upperTextColor;
    this->lowerTextColor = lowerTextColor;
    TinyText::backgroundColor = backgroundColor;
    upperController->setColor(textColor, backgroundColor);
    lowerController->setColor(lowerTextColor, backgroundColor);

}

void TinyText::setUpperText(std::string *text) {
    createIDTextArray(text, 0);

}

void TinyText::setLowerText(std::string *text) {
    createIDTextArray(text, 1);

}








