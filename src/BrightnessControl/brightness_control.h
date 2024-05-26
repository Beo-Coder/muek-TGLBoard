//
// Created by leo on 26.05.24.
//

#ifndef TGL_BOARD_SETTINGS_ENTRY_BRIGHTNESS_ENTRY_H
#define TGL_BOARD_BRIGHTNESS_CONTROL_BRIGHTNESS_CONTROL_H


class TinyText;
#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif

#include <string>

#include "display_program.h"

class BrightnessControl :public DisplayProgram{

    TinyText *tinyTextController;
    uint8_t *brightness;
    uint8_t lastBrightness;


    void setBrightness(int8_t dir);

    void updateText();
    std::string stringBuffer;



public:
    explicit BrightnessControl(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], TinyText* tinyTextController);


    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;

    void setBrightnessVar(uint8_t *globalBrightness);



};


#endif //TGL_BOARD_SETTINGS_ENTRY_BRIGHTNESS_ENTRY_H
