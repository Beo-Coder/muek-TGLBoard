//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_TEXTCONTROLLER_SCROLL_TEXT_H
#define TGL_BOARD_TEXTCONTROLLER_SCROLL_TEXT_H


namespace details_text_controller{
    class Subcontroller;
}

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "text_controller.h"


namespace details_scroll_text{
    inline const uint8_t SPACE_BETWEEN_LETTERS = 1;
}


class ScrollText : public TextController{



    bool leftShift;
    details_text_controller::Subcontroller *subcontroller;



    void createIDTextArray(const std::string *text) override;



public:
    explicit ScrollText(MatrixOutput *matrixOutput, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void setColor(const Color *textColor, const Color *backgroundColor) override;

    void setMode(bool leftShift = true);

    void createAndLoadFrame() override;



    void refresh() override;
    void restart() override;



};


#endif //TGL_BOARD_TEXTCONTROLLER_SCROLL_TEXT_H
