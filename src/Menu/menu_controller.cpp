//
// Created by leo on 26.05.24.
//

#include "menu_controller.h"
#include "menu_entry.h"
#include "TextController/text_controller.h"
#include "beo_common.h"

MenuController::MenuController(TextController *textController) {
    this->textController = textController;

    entryCount = 0;
    currentEntry = 0;

    switchMenuFlag = 0;
    switchMode = 0;

    button1State = false;
    button2State = false;

    button1Time = 0;
    button2Time = 0;

    timeWaitSwitchMode = 0;
    lastTextTime = 0;


}


void MenuController::addNewEntry(MenuEntry *entry) {
    if(entryCount <= details_menu_controller::MAX_ENTRIES_IN_MENU){
        entries[entryCount] = entry;
        entryCount++;
    }


}


void MenuController::button1ISR(bool state) {
    button1State = state;
    if(state){
        button1Time = beo::millis();
    }
    switch (switchMode){
        case 0:
            entries[currentEntry]->button1ISR(state);
            break;
        case 2:
            if(!state){
                switchMenuFlag = -1;
            }

            break;
        default:
            break;


    }

}

void MenuController::button2ISR(bool state) {
    button2State = state;
    if(state){
        button2Time =  beo::millis();
    }


    switch (switchMode){
        case 0:
            entries[currentEntry]->button2ISR(state);
            break;
        case 2:
            if(!state){
                switchMenuFlag = 1;
            }

            break;
        default:
            break;


    }


}


void MenuController::loop() {

    if(button1State && button2State){
        uint32_t time =  beo::millis();
        switch (switchMode){
            case 0:
                if(((time-button1Time) > details_menu_controller::HOLD_TIME_SWITCH) && ((time-button2Time) > details_menu_controller::HOLD_TIME_SWITCH)){
                    switchMode = 1;
                    switchEntry(0);
                    entries[currentEntry]->exitEntry();
                }
                break;
            case 1:
                break;
            case 2:

                switchMode = 3;
                entries[currentEntry]->restart();
                break;
            default:
                break;
        }

    }
    if(!button1State && !button2State){
        switch (switchMode){
            case 1:
                switchMode = 2;
                break;
            case 2:
                if(checkWaitTimeSelect()){
                    switchMode = 0;

                    entries[currentEntry]->restart();
                }
                break;
            case 3:
                switchMode = 0;
                break;
        }
    }
    if(switchMode == 1 || switchMode == 2){
        showText();
    }


    if(switchMode == 0 || switchMode == 3){
        entries[currentEntry]->loop();
    }else{
        if(switchMenuFlag != 0){
            switchEntry(switchMenuFlag);
            switchMenuFlag = 0;
        }
    }


}


void MenuController::switchEntry(int8_t direction) {


    if(currentEntry == 0 && direction == -1){
        currentEntry = entryCount-1;
    } else{
        currentEntry = (currentEntry+direction)%entryCount;
    }
    timeWaitSwitchMode = beo::millis();

    textController->restart();
    textController->setColor(&colorWhite, &colorBlank);
    textController->setText(entries[currentEntry]->getName());

}

bool MenuController::checkWaitTimeSelect() {
    return (beo::millis()-timeWaitSwitchMode) > details_menu_controller::WAIT_TIME_SELECT;
}

void MenuController::showText() {
    if((beo::millis()-lastTextTime) > details_menu_controller::TEXT_SPEED){
        lastTextTime = beo::millis();
        textController->refresh();
    }

}
