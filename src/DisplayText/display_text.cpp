//
// Created by leo on 26.05.24.
//

#include "display_text.h"
#include <string>
#include "PIOMatrixOutput/color.h"
#include "TextController/text_controller.h"

const uint8_t textCount = 3;
const std::string text[] = {" Hello World! ", " ... ", " :) "};

const uint8_t colorCount = 6;
const Color* colors[] = {&colorPurple, &colorBlue,&colorCyan, &colorGreen, &colorYellow, &colorRed};




DisplayText::DisplayText(MatrixOutput *ledMatrix, Color (*frame)[8][16], TextController *textController) : DisplayProgram(ledMatrix, frame) {
    this->textController = textController;
    currentTextIndex = 0;
    currentColorIndex = 0;

    newText = false;
    newColor = false;

    refreshSpeed = 120;


}

void DisplayText::refresh() {
    if(newText){
        newText = false;
        setText(currentTextIndex);
    }
    if(newColor){
        newColor = false;
        setColor(currentColorIndex);
    }
    textController->createAndLoadFrame();
    matrix->setDisplayData(frame);
    matrix->sendData();


}

void DisplayText::restart() {
    currentTextIndex = 0;
    currentColorIndex = 0;
    setText(currentTextIndex);
    setColor(currentColorIndex);
    clearFrame();



}

void DisplayText::button1ISR(bool state) {
    if(!state){
        newColor = true;
        currentColorIndex = (currentColorIndex + 1)%colorCount;
    }

}

void DisplayText::button2ISR(bool state) {
    if(!state) {
        newText = true;
        currentTextIndex = (currentTextIndex + 1) % textCount;
    }




}

void DisplayText::setText(uint8_t index) {
    textController->setText(&(text[index]));
    // clearFrame();

}

void DisplayText::setColor(uint8_t index) {
    textController->setColor(colors[index], &colorBlank);

}
