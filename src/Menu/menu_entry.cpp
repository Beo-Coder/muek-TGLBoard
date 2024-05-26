//
// Created by leo on 26.05.24.
//

#include "menu_entry.h"
#include "display_program.h"
#include "beo_common.h"


MenuEntry::MenuEntry() {
    currentProgramIndex = 0;
    programCount = 0;
    lastLoop = 0;
    switchProgramFlag = 0;

}

void MenuEntry::button1ISR(bool state) {
    if(programCount <= 1){
        program[currentProgramIndex]->button1ISR(state);
    }else{
        if(!state){
            switchProgramFlag = -1;
        }
    }

}

void MenuEntry::button2ISR(bool state) {
    if(programCount <= 1){
        program[currentProgramIndex]->button2ISR(state);
    }else{
        if(!state){
            switchProgramFlag = 1;
        }
    }

}


void MenuEntry::switchProgram(int8_t direction) {
    if(currentProgramIndex == 0 && direction == -1){
        currentProgramIndex = programCount -1;
    } else{
        currentProgramIndex = (currentProgramIndex+direction)%programCount;
    }

    program[currentProgramIndex]->restart();

}

void MenuEntry::loop() {

    if(switchProgramFlag != 0){
        switchProgram(switchProgramFlag);
        switchProgramFlag = 0;
    }

    if(beo::millis()-lastLoop > program[currentProgramIndex]->refreshSpeed || program[currentProgramIndex]->refreshSpeed == 0){
        lastLoop = beo::millis();
        program[currentProgramIndex]->refresh();

    }

}


void MenuEntry::addProgram(DisplayProgram *newProgram) {
    if(programCount <=MAX_PROGRAMS_IN_ENTRY){
        program[programCount] = newProgram;
        programCount++;
    }

}

void MenuEntry::restart() {
    program[currentProgramIndex]->restart();

}

void MenuEntry::setName(std::string name) {
    this->name = name;
}

std::string* MenuEntry::getName() {
    return &name;
}









