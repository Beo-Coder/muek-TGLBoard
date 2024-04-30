//
// Created by leo on 03.04.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_COLOR_H
#define MUEK_ARGB_MATRIX_BOARD_COLOR_H

#include "Arduino.h"

#define MAX_COLOR_VALUE 255
#define MIN_COLOR_VALUE 0

#define NORMAL_BRIGHTNESS 1


class Color {



    float brightness;


    static float checkAndReturnValid(float value);

public:

    float blue;
    float red;
    float green;

    void setRed(float value);
    void setGreen(float value);
    void setBlue(float value);

    float getRed(bool raw=false);
    float getGreen(bool raw=false);
    float getBlue(bool raw=false);

    void setRGB(uint8_t colorNumber, float value); // 0: red; 1: green; 2: blue
    float getRGB(uint8_t colorNumber, bool raw=false); // 0: red; 1: green; 2: blue

    void setBrightness(float value);
    float getBrightness();



    Color(float red, float green, float blue);
    Color();

    uint32_t calc();
};

// Clear "color"
static Color colorBlank(0,0,0);

// Some static colors
static Color colorRed(1,0,0);
static Color colorGreen(0,1,0);
static Color colorBlue(0,0,1);

static Color colorWhite(1,1,1);
static Color colorYellow(1,1,0);
static Color colorCyan(0,1,1);
static Color colorPurple(1,0,1);

#define NUMBER_NORMAL_COLORS 7
static Color *allColors[NUMBER_NORMAL_COLORS] = {&colorRed, &colorBlue, &colorGreen, &colorWhite, &colorYellow, &colorCyan, &colorPurple};


#endif //MUEK_ARGB_MATRIX_BOARD_COLOR_H
