//
// Created by leo on 11.05.24.
//

#ifndef TGL_BOARD_TEXTCONTROLLER_STATIC_TEXT_H
#define TGL_BOARD_TEXTCONTROLLER_STATIC_TEXT_H

namespace details_text_controller{
    class StaticSubcontroller;
}

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "text_controller.h"


namespace details_static_text{
    static const uint8_t SPACE_BETWEEN_LETTERS = 1;
}

class StaticText : public TextController {

    bool textInitialized;

    details_text_controller::StaticSubcontroller *subcontroller;

    void createIDTextArray(std::string *text) override;

public:

    explicit StaticText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void setText(std::string *text) override;

    void setColor(Color *textColor, Color *backgroundColor) override;

    void createAndLoadFrame() override;

    void refresh() override;

    void restart() override;


};


#endif //TGL_BOARD_TEXTCONTROLLER_STATIC_TEXT_H
