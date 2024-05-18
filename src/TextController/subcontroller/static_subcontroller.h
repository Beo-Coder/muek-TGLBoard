//
// Created by leo on 17.05.24.
//

#ifndef TGL_BOARD_TEXTCONTROLLER_STATIC_SUBCONTROLLER_H
#define TGL_BOARD_TEXTCONTROLLER_STATIC_SUBCONTROLLER_H


#include <Arduino.h>
#include "subcontroller.h"

namespace details_text_controller {

    static const uint8_t NUMBER_FREE_SPACES = 1; // Added after the text, if the text scrolls
    static const uint8_t WAIT_TIME_BEGIN = 4;
    static const uint8_t WAIT_TIME_END = 4;

    class StaticSubcontroller : public Subcontroller{

        bool needScrolling;
        uint8_t staticTextTime;
        uint8_t state;



        void shiftAllTheWayLeft();

        void shiftAllTheWayRight();

    public:
        StaticSubcontroller(uint16_t idArrayOffset, uint16_t yPos, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH],
                            uint8_t *idTextArray, Charset *charset, Color *textColor, Color *backgroundColor);

        void initText();

        void refreshText();


    };
}


#endif //TGL_BOARD_TEXTCONTROLLER_STATIC_SUBCONTROLLER_H
