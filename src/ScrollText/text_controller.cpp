//
// Created by leo on 11.05.24.
//

#include "text_controller.h"

TextController::TextController(MatrixOutput *matrix, Color (*frame)[8][16]) : display_program(matrix, frame) {
    idTextArraySize = 0;
    idTextArrayIndex = 0;
    textColor = &colorRed;
    backgroundColor = &colorBlank;
}

void TextController::setText(String *text, bool clearDisplay) {
    if(clearDisplay){
        clearFrame();
    }
    createIDTextArray(text);
}

void TextController::setColor(Color *textColor, Color *backgroundColor) {
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;

}





void TextController::button1ISR(bool state) {

}

void TextController::button2ISR(bool state) {

}


