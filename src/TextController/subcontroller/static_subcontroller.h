//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_TEXTCONTROLLER_STATIC_SUBCONTROLLER_H
#define TGL_BOARD_TEXTCONTROLLER_STATIC_SUBCONTROLLER_H


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "subcontroller.h"

namespace details_text_controller {

    inline const uint8_t NUMBER_FREE_SPACES = 1; // Added after the text, if the text scrolls
    inline const uint8_t WAIT_TIME_BEGIN = 4;
    inline const uint8_t WAIT_TIME_END = 4;

    class StaticSubcontroller : public Subcontroller{

        bool needScrolling;
        uint8_t staticTextTime;
        uint8_t state;



        void shiftAllTheWayLeft();

        void shiftAllTheWayRight();

    public:
        StaticSubcontroller(uint16_t idArrayOffset, uint16_t yPos, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH],
                            uint8_t *idTextArray, const Charset *charset, const Color *textColor, const Color *backgroundColor);

        void initText();

        void refreshText();


    };
}


#endif //TGL_BOARD_TEXTCONTROLLER_STATIC_SUBCONTROLLER_H
