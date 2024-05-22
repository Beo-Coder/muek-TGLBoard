//
// Created by leo on 14.05.24.
//

#ifndef TGL_BOARD_TEXTCONTROLLER_TINY_LETTERS_H
#define TGL_BOARD_TEXTCONTROLLER_TINY_LETTERS_H

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include <string>

namespace details_letters_tiny {


// alphabet
    extern const uint8_t tinyA[];
    extern const uint8_t tinyB[]; // similar to 6
    extern const uint8_t tinyC[];
    extern const uint8_t tinyD[];
    extern const uint8_t tinyE[]; // hmm
    extern const uint8_t tinyF[];
    extern const uint8_t tinyG[];
    extern const uint8_t tinyH[]; // similar to n
    extern const uint8_t tinyI[];
    extern const uint8_t tinyJ[];
    extern const uint8_t tinyK[];
    extern const uint8_t tinyL[];
    extern const uint8_t tinyM[];
    extern const uint8_t tinyN[];
    extern const uint8_t tinyO[]; // similar to 0
    extern const uint8_t tinyP[];
    extern const uint8_t tinyQ[];
    extern const uint8_t tinyR[];
    extern const uint8_t tinyS[]; // similar to 5
    extern const uint8_t tinyT[];
    extern const uint8_t tinyU[];
    extern const uint8_t tinyV[];
    extern const uint8_t tinyW[];
    extern const uint8_t tinyX[];
    extern const uint8_t tinyY[];
    extern const uint8_t tinyZ[]; // similar to 2

// digits
    extern const uint8_t tiny0[];
    extern const uint8_t tiny1[];
    extern const uint8_t tiny2[];
    extern const uint8_t tiny3[]; // hmm
    extern const uint8_t tiny4[];
    extern const uint8_t tiny5[];
    extern const uint8_t tiny6[];
    extern const uint8_t tiny7[];
    extern const uint8_t tiny8[]; // hmm, very hmm
    extern const uint8_t tiny9[];

// special chars:
    extern const uint8_t tiny_[];
    extern const uint8_t tiny_1[];
    extern const uint8_t tiny_2[];

    extern const uint8_t tinyUnderscore[];
    extern const uint8_t tinyPipe[];

    extern const uint8_t tinyRoundBracketO[];
    extern const uint8_t tinyRoundBracketC[];

    extern const uint8_t tinySquareBracketO[]; // very similar to C
    extern const uint8_t tinySquareBracketC[];

    extern const uint8_t tinyDot[];
    extern const uint8_t tinyComma[];
    extern const uint8_t tinyQuestionMark[]; // hmm
    extern const uint8_t tinyExclamationMark[]; // hmm

    extern const uint8_t tinyDash[];
    extern const uint8_t tinyColon[];
    extern const uint8_t tinySemiColon[];

    extern const uint8_t tinyPlus[];
    extern const uint8_t tinySlash[];
    extern const uint8_t tinyBackSlash[];


    extern const uint8_t breakChar[];


    extern const std::string tinyNormalChars;
    extern const std::string tinySpecialChars;

    extern const uint16_t SINGLE_SPACE_INDEX;

    extern const uint16_t breakCharSpecialIndex;


    extern const uint8_t *tinyLetter[];

}
#endif //TGL_BOARD_TEXTCONTROLLER_TINY_LETTERS_H
