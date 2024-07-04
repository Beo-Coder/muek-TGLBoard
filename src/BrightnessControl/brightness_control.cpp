//
// Created by leo on 26.05.24.
//

#include "brightness_control.h"
#include "TextController/tiny_text.h"
#include "FlashController/flash_controller.h"


const std::string upperText = "Brightness";

BrightnessControl::BrightnessControl(MatrixOutput *ledMatrix, Color (*frame)[8][16], TinyText *tinyTextController, FlashController* flashController) : DisplayProgram(ledMatrix, frame) {
    this->tinyTextController = tinyTextController;
    stringBuffer = "";
    refreshSpeed = 120;
    lastBrightness = UINT8_MAX;

    this->flashController = flashController;
    flashKey = 0;



}







void BrightnessControl::setBrightnessVar(uint32_t *globalBrightness) {
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

void BrightnessControl::saveBrightness(bool readOverride) {
    if(getBrightnessFromFlash() != *brightness || readOverride){
        flashController->writeData(flashKey, (uint8_t*)brightness);
    }
}


void BrightnessControl::exit() {
    saveBrightness();

}

void BrightnessControl::setBrightnessFlashKey(uint8_t flashKey) {
    this->flashKey = flashKey;

}

uint32_t BrightnessControl::getBrightnessFromFlash() {
    uint8_t *address = FlashController::readData(flashKey);
    if(address == nullptr){
        return NORMAL_BRIGHTNESS;
    }
    uint32_t flashBrightness = 0;
    for(uint32_t i=0; i<4; i++){
        flashBrightness |= ((*(address+i)) << (8*i));
    }
    if(flashBrightness > MAX_BRIGHTNESS){
        flashBrightness = MAX_BRIGHTNESS;
        *brightness = MAX_BRIGHTNESS;

    }
    if(flashBrightness < MIN_BRIGHTNESS){
        flashBrightness = MIN_BRIGHTNESS;
        *brightness = MIN_BRIGHTNESS;

    }
    return flashBrightness;
}

void BrightnessControl::loadBrightnessFromFlash() {
    *brightness = getBrightnessFromFlash();
    saveBrightness(true);

}






