//
// Created by leo on 11.05.24.
//

#include "static_text.h"
#include "charsets/charset.h"
#include "subcontroller/static_subcontroller.h"


StaticText::StaticText(MatrixOutput *matrixOutput, Color (*frame)[8][16]) : TextController(matrixOutput, frame) {

    refreshSpeed = 120;
    subcontroller = new details_text_controller::StaticSubcontroller(0, 0, frame, idTextArray, &normalLetters,
                                                                     textColor, backgroundColor);


}


void StaticText::setText(String *text) {
    TextController::setText(text);
    subcontroller->initText();
}


void StaticText::createAndLoadFrame() {
    subcontroller->refreshText();

    matrix->setDisplayData(frame);
}

void StaticText::refresh() {
    createAndLoadFrame();
    matrix->sendData();

}

void StaticText::restart() {


}

void StaticText::createIDTextArray(String *text) {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    for (unsigned int i = 0; i < text->length(); i++) {
        char charAtIndex = text->charAt(i);
        if (charAtIndex == '%') {
            charAtIndex = text->charAt(i + 1);
            int index = details_letters_normal::specialChars.indexOf(charAtIndex);
            if (index != -1) {
                idTextArray[idTextArraySize] = index + details_letters_normal::normalChars.length();
                i++;
            }

        } else {
            int index = details_letters_normal::normalChars.indexOf(charAtIndex);
            if (index != -1) {
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

void StaticText::setColor(Color *textColor, Color *backgroundColor) {
    TextController::setColor(textColor, backgroundColor);
    subcontroller->setColor(textColor, backgroundColor);
}






