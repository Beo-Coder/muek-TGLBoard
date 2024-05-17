//
// Created by leo on 14.05.24.
//

#ifndef MUEK_TGL_BOARD2_TINY_TEXT_H
#define MUEK_TGL_BOARD2_TINY_TEXT_H

namespace details_text_controller{
    class StaticSubcontroller;
}
class Color;
class MatrixOutput;
#include <Arduino.h>
#include "text_controller.h"



namespace details_tiny_text{
    static const uint8_t SUBMATRIX_HEIGHT = (MATRIX_HEIGHT/2);
    static const uint8_t SPACE_BETWEEN_LETTERS = 1;
}



class TinyText : public TextController {

    Color *lowerTextColor;

    details_text_controller::StaticSubcontroller *upperController;
    details_text_controller::StaticSubcontroller *lowerController;


    uint16_t *upperTextArraySize = &idTextArraySize;

    uint16_t lowerTextArraySize;


    void createIDTextArray(String *text) override;
    void createIDTextArray(String *text, uint8_t startIndex);


public:

    explicit TinyText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void setText(String *text) override;

    void setUpperText(String *text);
    void setLowerText(String *text);

    void setColor(Color *upperTextColor,Color *lowerTextColor,Color *backgroundColor);


    void createAndLoadFrame() override;

    void refresh() override;

    void restart() override;

};


#endif //MUEK_TGL_BOARD2_TINY_TEXT_H
