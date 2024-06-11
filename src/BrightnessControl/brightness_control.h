//
// Created by leo on 26.05.24.
//

#ifndef TGL_BOARD_SETTINGS_ENTRY_BRIGHTNESS_ENTRY_H
#define TGL_BOARD_BRIGHTNESS_CONTROL_BRIGHTNESS_CONTROL_H


class TinyText;
class FlashController;
#ifdef ARDUINO
#include <Arduino.h>
#else
#include "pico/stdlib.h"
#endif

#include <string>

#include "display_program.h"

class BrightnessControl :public DisplayProgram{

    TinyText *tinyTextController;
    uint32_t *brightness;
    uint32_t lastBrightness;

    FlashController* flashController;
    uint8_t flashKey;
    uint32_t getBrightnessFromFlash() const;



    void setBrightness(int8_t dir);

    void updateText();
    std::string stringBuffer;

    void saveBrightness();



public:
    explicit BrightnessControl(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], TinyText* tinyTextController, FlashController* flashController);


    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;

    void setBrightnessVar(uint32_t *globalBrightness);
    void setBrightnessFlashKey(uint8_t flashKey);

    void loadBrightnessFromFlash();

    void exit() override;



};


#endif //TGL_BOARD_SETTINGS_ENTRY_BRIGHTNESS_ENTRY_H
