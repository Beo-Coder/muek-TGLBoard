//
// Created by leo on 26.05.24.
//

#ifndef TGL_BOARD_MENU_MENU_CONTROLLER_H
#define TGL_BOARD_MENU_MENU_CONTROLLER_H

class MenuEntry;
class TextController;
#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif


#define HOLD_TIME_SWITCH (2000)
#define WAIT_TIME_SELECT (10000)
#define TEXT_SPEED (80)
#define MAX_ENTRIES_IN_MENU 6

class MenuController {


    TextController *textController;

    bool button1State;
    bool button2State;
    uint32_t button1Time;
    uint32_t button2Time;

    uint8_t switchMode;
    int8_t switchMenuFlag;

    uint32_t timeWaitSwitchMode;
    uint32_t lastTextTime;

    uint8_t currentEntry;
    uint8_t lastEntry;
    uint8_t entryCount;
    MenuEntry* entries[MAX_ENTRIES_IN_MENU];

    void switchEntry(int8_t direction);
    bool checkWaitTimeSelect();
    void showText();

public:

    explicit MenuController(TextController *textController);
    void addNewEntry(MenuEntry* entry);



    void button1ISR(bool state);
    void button2ISR(bool state);
    void loop();




};


#endif //TGL_BOARD_MENU_MENU_CONTROLLER_H
