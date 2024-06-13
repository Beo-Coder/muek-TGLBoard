//
// Created by leo on 14.05.24.
//

#ifndef TGL_BOARD_TEXTCONTROLLER_TINY_TEXT_H
#define TGL_BOARD_TEXTCONTROLLER_TINY_TEXT_H

namespace details_text_controller{
    class StaticSubcontroller;
}
class Color;
class MatrixOutput;

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif


#include "text_controller.h"



namespace details_tiny_text{
    inline const uint8_t SUBMATRIX_HEIGHT = (MATRIX_HEIGHT/2);
    inline const uint8_t SPACE_BETWEEN_LETTERS = 1;
}



class TinyText : public TextController {

    const Color *lowerTextColor;

    details_text_controller::StaticSubcontroller *upperController;
    details_text_controller::StaticSubcontroller *lowerController;


    uint16_t *upperTextArraySize = &idTextArraySize;

    uint16_t lowerTextArraySize;


    void createIDTextArray(const std::string *text) override;
    void createIDTextArray(const std::string *text, uint8_t startIndex);


public:

    explicit TinyText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void setText(const std::string *text) override;

    void setUpperText(const std::string *text);
    void setLowerText(const std::string *text);

    void setColor(const Color *upperTextColor, const Color *lowerTextColor, const Color *backgroundColor);


    void createAndLoadFrame() override;

    void refresh() override;

    void restart() override;

};


#endif //TGL_BOARD_TEXTCONTROLLER_TINY_TEXT_H
