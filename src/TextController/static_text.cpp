//
// © 2024 Leonhard Baschang
//

#include "static_text.h"
#include "charsets/charset.h"
#include "subcontroller/static_subcontroller.h"


StaticText::StaticText(MatrixOutput *matrixOutput, Color (*frame)[8][16]) : TextController(matrixOutput, frame) {

    refreshSpeed = 120;
    textInitialized = false;
    subcontroller = new details_text_controller::StaticSubcontroller(0, 0, frame, idTextArray, &normalLetters,
                                                                     textColor, backgroundColor);


}


void StaticText::setText(const std::string *text) {
    TextController::setText(text);
    textInitialized = false;
}


void StaticText::createAndLoadFrame() {
    if(!textInitialized){
        subcontroller->initText();
        textInitialized = true;
    }
    subcontroller->refreshText();

    matrix->setDisplayData(frame);
}

void StaticText::refresh() {
    createAndLoadFrame();
    matrix->sendData();

}

void StaticText::restart() {
    textInitialized = false;
    idTextArraySize = 0;
    idTextArrayIndex = 0;


}

void StaticText::createIDTextArray(const std::string *text) {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
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
        for (int j = 0; j < details_static_text::SPACE_BETWEEN_LETTERS; j++) {
            idTextArray[idTextArraySize] = details_letters_normal::SINGLE_SPACE_INDEX;
            idTextArraySize++;
        }

    }
    subcontroller->setArraySize(idTextArraySize);

}

void StaticText::setColor(const Color *textColor, const Color *backgroundColor) {
    TextController::setColor(textColor, backgroundColor);
    subcontroller->setColor(textColor, backgroundColor);
}






