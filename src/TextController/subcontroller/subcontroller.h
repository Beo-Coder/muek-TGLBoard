//
// Created by leo on 17.05.24.
//

#ifndef MUEK_TGL_BOARD2_SUBCONTROLLER_H
#define MUEK_TGL_BOARD2_SUBCONTROLLER_H

class Color;
struct Charset;

#include <Arduino.h>
#include "PIOMatrixOutput/pio_matrix_output.h"


namespace details_text_controller{
    class Subcontroller {



    protected:

        Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH];
        uint8_t *idTextArray;
        Color *textColor;
        Color *backgroundColor;
        Charset *charset;





        uint16_t idArrayOffset;
        uint16_t yPos;

        uint16_t idArraySize;
        uint16_t idArrayIndex;
        uint8_t idArrayBitOffset;



    public:
        explicit Subcontroller(uint16_t idArrayOffset, uint16_t yPos, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], uint8_t *idTextArray, Charset *charset, Color *textColor, Color *backgroundColor);

        void setArraySize(uint16_t size);

        void shiftTextLeft();
        void shiftTextRight();

        void loadNewDataLeftShift(bool loadFrame = true);
        void loadNewDataRightShift(bool loadFrame = true);

        void setIdArrayIndex(uint16_t idArrayIndex);

        void setColor(Color *textColor, Color *backgroundColor);




    };
}



#endif //MUEK_TGL_BOARD2_SUBCONTROLLER_H
