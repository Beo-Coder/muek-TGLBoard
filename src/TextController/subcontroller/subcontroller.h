//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_TEXTCONTROLLER_SUBCONTROLLER_H
#define TGL_BOARD_TEXTCONTROLLER_SUBCONTROLLER_H

class Color;
struct Charset;

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "PIOMatrixOutput/pio_matrix_output.h"


namespace details_text_controller{
    class Subcontroller {



    protected:

        Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH];
        uint8_t *idTextArray;
        const Color *textColor;
        const Color *backgroundColor;
        const Charset *charset;





        uint16_t idArrayOffset;
        uint16_t yPos;

        uint16_t idArraySize;
        uint16_t idArrayIndex;
        uint8_t idArrayBitOffset;



    public:
        explicit Subcontroller(uint16_t idArrayOffset, uint16_t yPos, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t *idTextArray, const Charset *charset, const Color *textColor, const Color *backgroundColor);

        void setArraySize(uint16_t size);

        void shiftTextLeft();
        void shiftTextRight();

        void loadNewDataLeftShift(bool loadFrame = true);
        void loadNewDataRightShift(bool loadFrame = true);

        void setIdArrayIndex(uint16_t idArrayIndex);

        void setColor(const Color *textColor, const Color *backgroundColor);




    };
}



#endif //TGL_BOARD_TEXTCONTROLLER_SUBCONTROLLER_H
