//
// Created by leo on 26.05.24.
//

#ifndef TGL_BOARD_MENU_MENU_ENTRY_H
#define TGL_BOARD_MENU_MENU_ENTRY_H

class DisplayProgram;
class Color;

#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif
#include "PIOMatrixOutput/pio_matrix_settings.h"
#include <string>

#define MAX_PROGRAMS_IN_ENTRY 10


class MenuEntry {

    uint32_t lastLoop;

    int8_t switchProgramFlag;

    uint8_t currentProgramIndex;
    uint8_t programCount;
    DisplayProgram *program[MAX_PROGRAMS_IN_ENTRY];

    std::string name;

    void switchProgram(int8_t direction);


public:
    MenuEntry();
    void addProgram(DisplayProgram *program);


    void button1ISR(bool state);
    void button2ISR(bool state);

    void loop();
    void restart();
    void exitEntry();
    void setName(std::string name);
    std::string* getName();

};


#endif //TGL_BOARD_MENU_MENU_ENTRY_H
