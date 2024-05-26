//
// Created by leo on 26.05.24.
//

#include "brightness_control.h"
#include "TextController/tiny_text.h"



const std::string upperText = "Brightness";

BrightnessControl::BrightnessControl(MatrixOutput *ledMatrix, Color (*frame)[8][16], TinyText *tinyTextController) : DisplayProgram(ledMatrix, frame) {
    this->tinyTextController = tinyTextController;
    stringBuffer = "";
    refreshSpeed = 120;
    lastBrightness = UINT8_MAX;



}







void BrightnessControl::setBrightnessVar(uint8_t *globalBrightness) {
    brightness = globalBrightness;
}

void BrightnessControl::setBrightness(int8_t dir) {
    if(*brightness == MIN_BRIGHTNESS && dir == -1)return;
    if(*brightness == MAX_BRIGHTNESS && dir == 1) return;
    *brightness = *brightness + dir;

}

void BrightnessControl::updateText() {
    stringBuffer = "";
    stringBuffer.append(std::to_string(*brightness));
    tinyTextController->setLowerText(&stringBuffer);

}




void BrightnessControl::refresh() {
    if(lastBrightness != *brightness){
        updateText();
        lastBrightness = *brightness;
    }
    tinyTextController->createAndLoadFrame();
    matrix->setDisplayData(frame);
    matrix->sendData();

}

void BrightnessControl::button1ISR(bool data) {
    if(!data){
        setBrightness(-1);
    }


}

void BrightnessControl::button2ISR(bool data) {
    if(!data){
        setBrightness(1);
    }

}



void BrightnessControl::restart() {
    tinyTextController->restart();
    tinyTextController->setColor(&colorCyan, &colorWhite, &colorBlank);
    tinyTextController->setUpperText(&upperText);
    updateText();
    lastBrightness = *brightness;

}




