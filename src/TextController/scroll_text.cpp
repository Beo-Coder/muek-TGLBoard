//
// © 2024 Leonhard Baschang
//

#include "scroll_text.h"
#include "charsets/charset.h"
#include "subcontroller/subcontroller.h"

ScrollText::ScrollText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]) : TextController(
        matrixOutput, frame) {
    idTextArraySize = 0;

    subcontroller = new details_text_controller::Subcontroller(0,0,frame,idTextArray,&normalLetters,textColor,backgroundColor);

    leftShift = true;

    refreshSpeed = 120;


}

void ScrollText::createIDTextArray(const std::string *text) {
    idTextArraySize = 0;
    for (unsigned int i = 0; i < text->length(); i++) {
        char charAtIndex = text->at(i);
        if (charAtIndex == '%') {
            charAtIndex = text->at(i + 1);
            unsigned int index = details_letters_normal::specialChars.find(charAtIndex);
            if (index != std::string::npos) {
                idTextArray[idTextArraySize] = index + details_letters_normal::normalChars.length();
                i++;
            }

        } else {
            unsigned int index = details_letters_normal::normalChars.find(charAtIndex);
            if (index != std::string::npos) {
                idTextArray[idTextArraySize] = index;
            }
        }
        idTextArraySize++;

        // Add spaces between letters
        for (int j = 0; j < details_scroll_text::SPACE_BETWEEN_LETTERS; j++) {
            idTextArray[idTextArraySize] = details_letters_normal::SINGLE_SPACE_INDEX;
            idTextArraySize++;
        }
        setMode(leftShift);

    }
    subcontroller->setArraySize(idTextArraySize);

}





void ScrollText::createAndLoadFrame() {
    if (leftShift) {
        subcontroller->shiftTextLeft();
        subcontroller->loadNewDataLeftShift();
    } else {
        subcontroller->shiftTextRight();
        subcontroller->loadNewDataRightShift();
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
    subcontroller->setIdArrayIndex(idTextArrayIndex);

}




void ScrollText::refresh() {

    createAndLoadFrame();
    matrix->sendData();
}


void ScrollText::restart() {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    leftShift = true;
}

void ScrollText::setColor(const Color *textColor, const Color *backgroundColor) {
    TextController::setColor(textColor, backgroundColor);
    subcontroller->setColor(textColor, backgroundColor);
}















