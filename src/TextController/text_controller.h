//
// Created by leo on 11.05.24.
//

#ifndef TGL_BOARD_TEXTCONTROLLER_TEXT_CONTROLLER_H
#define TGL_BOARD_TEXTCONTROLLER_TEXT_CONTROLLER_H

class Color;
class MatrixOutput;

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "display_program.h"
#include <string>


#define MAX_TEXT_LENGTH 500


class TextController : public display_program {

protected:

    inline static uint8_t idTextArray[MAX_TEXT_LENGTH]{0};
    inline static uint16_t idTextArraySize{0};
    inline static uint16_t idTextArrayIndex{0};


    inline static Color *textColor{nullptr};
    inline static Color *backgroundColor{nullptr};


    virtual void createIDTextArray(std::string *text) = 0;

public:

    TextController(MatrixOutput *matrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    virtual void setText(std::string *text);

    virtual void setColor(Color *textColor, Color *backgroundColor);

    virtual void createAndLoadFrame() = 0;


    void button1ISR(bool state) override;

    void button2ISR(bool state) override;


};


#endif //TGL_BOARD_TEXTCONTROLLER_TEXT_CONTROLLER_H
