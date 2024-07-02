//
// Created by leo on 03.04.24.
//

#ifndef TGL_BOARD_PIO_MATRIX_OUTPUT_COLOR_H
#define TGL_BOARD_PIO_MATRIX_OUTPUT_COLOR_H


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif
#include "pio_matrix_settings.h"
#include <cmath>



#define NORMAL_BITS 8
#define MAX_COLOR_VALUE_RAW ((1 << (NORMAL_BITS+(uint8_t)log2(MAX_SUBFRAMES))) - 1)
#define MAX_COLOR_VALUE_SET ((1<<NORMAL_BITS)-1)
#define MIN_COLOR_VALUE 0


#define NORMAL_BRIGHTNESS 1


#define MIN_BRIGHTNESS 1
#define MAX_BRIGHTNESS 25
extern uint32_t globalBrightness;


class Color {

    uint16_t blue;
    uint16_t red;
    uint16_t green;



public:
    static uint16_t checkAndReturnValid(uint16_t value);
    static uint16_t calcFixedPointNumber(float value);
    static float calcFloatingPointNumber(uint16_t value);
    static uint8_t toUint8(uint16_t value);
    static uint8_t getNumberOfActiveSubframes(uint16_t value);





    bool equals(Color* reference) const;

    void set(Color* reference);
    void add(Color* addition);
    void multiply(float factor);
    void average(Color* addition);

    void setRed(float value);
    void setGreen(float value);
    void setBlue(float value);


    void setRedRaw(uint16_t value);
    void setGreenRaw(uint16_t value);
    void setBlueRaw(uint16_t value);

    float getRed() const;
    float getGreen() const;
    float getBlue() const;


    uint16_t getRedRaw() const;
    uint16_t getGreenRaw() const;
    uint16_t getBlueRaw() const;






    Color(float red, float green, float blue);
    Color();

    /**
     * Only for internal use
     **/
    uint32_t calc() const;

    /**
     * Only for internal use
     **/
    uint16_t getRed8Bit() const;

    /**
     * Only for internal use
     **/
    uint16_t getGreen8Bit() const;

    /**
     * Only for internal use
     **/
    uint16_t getBlue8Bit() const;

    /**
     * Only for internal use
     **/
    uint8_t getRedActiveSubframes() const;

    /**
     * Only for internal use
     **/
    uint8_t getGreenActiveSubframes() const;

    /**
     * Only for internal use
     **/
    uint8_t getBlueActiveSubframes() const;


};


inline Color colorBlank(0,0,0);

// Some static colors
inline Color colorRed(NORMAL_BRIGHTNESS,0,0);
inline Color colorGreen(0,NORMAL_BRIGHTNESS,0);
inline Color colorBlue(0,0,NORMAL_BRIGHTNESS);

inline Color colorWhite(NORMAL_BRIGHTNESS,NORMAL_BRIGHTNESS,NORMAL_BRIGHTNESS);
inline Color colorYellow(NORMAL_BRIGHTNESS,NORMAL_BRIGHTNESS,0);
inline Color colorCyan(0,NORMAL_BRIGHTNESS,NORMAL_BRIGHTNESS);
inline Color colorPurple(NORMAL_BRIGHTNESS,0,NORMAL_BRIGHTNESS);

inline Color colorOrange(NORMAL_BRIGHTNESS,NORMAL_BRIGHTNESS*0.5,0);
inline Color colorPink(NORMAL_BRIGHTNESS, 0, NORMAL_BRIGHTNESS * 0.5);


inline Color *allColors[] = {&colorRed, &colorBlue, &colorGreen, &colorWhite, &colorYellow, &colorCyan, &colorPurple};

#endif //TGL_BOARD_PIO_MATRIX_OUTPUT_COLOR_H
