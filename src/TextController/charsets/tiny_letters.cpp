//
// Created by leo on 21.05.24.
//



#include "tiny_letters.h"

namespace details_letters_tiny {


// alphabet
    const uint8_t tinyA[] = {0b010, 0b101, 0b111, 0b101, 3};
    const uint8_t tinyB[] = {0b100, 0b110, 0b101, 0b111, 3}; // similar to 6
    const uint8_t tinyC[] = {0b111, 0b100, 0b100, 0b111, 3};
    const uint8_t tinyD[] = {0b001, 0b111, 0b101, 0b111, 3};
    const uint8_t tinyE[] = {0b111, 0b111, 0b100, 0b111, 3}; // hmm
    const uint8_t tinyF[] = {0b111, 0b100, 0b110, 0b100, 3};
    const uint8_t tinyG[] = {0b111, 0b100, 0b101, 0b111, 3};
//const uint8_t tinyH[] = {0b101, 0b111, 0b111,0b101, 3}; // this or
    const uint8_t tinyH[] = {0b100, 0b100, 0b111, 0b101, 3}; // similar to n
    const uint8_t tinyI[] = {0b111, 0b010, 0b010, 0b111, 3};
    const uint8_t tinyJ[] = {0b001, 0b001, 0b101, 0b010, 3};
    const uint8_t tinyK[] = {0b101, 0b110, 0b110, 0b101, 3};
    const uint8_t tinyL[] = {0b100, 0b100, 0b100, 0b111, 3};
    const uint8_t tinyM[] = {0b101, 0b111, 0b101, 0b101, 3};
    const uint8_t tinyN[] = {0b100, 0b111, 0b101, 0b101, 3};
    const uint8_t tinyO[] = {0b111, 0b101, 0b101, 0b111, 3}; // similar to 0
    const uint8_t tinyP[] = {0b111, 0b101, 0b111, 0b100, 3};
    const uint8_t tinyQ[] = {0b111, 0b101, 0b111, 0b001, 3};
    const uint8_t tinyR[] = {0b111, 0b101, 0b110, 0b101, 3};
    const uint8_t tinyS[] = {0b111, 0b100, 0b011, 0b111, 3}; // similar to 5
    const uint8_t tinyT[] = {0b111, 0b010, 0b010, 0b010, 3};
    const uint8_t tinyU[] = {0b101, 0b101, 0b101, 0b111, 3};
    const uint8_t tinyV[] = {0b101, 0b101, 0b101, 0b010, 3};
    const uint8_t tinyW[] = {0b101, 0b101, 0b111, 0b101, 3};
    const uint8_t tinyX[] = {0b101, 0b010, 0b010, 0b101, 3};
    const uint8_t tinyY[] = {0b101, 0b101, 0b010, 0b010, 3};
    const uint8_t tinyZ[] = {0b111, 0b001, 0b010, 0b111, 3}; // similar to 2

// digits
    const uint8_t tiny0[] = {0b111, 0b111, 0b101, 0b111, 3};
    const uint8_t tiny1[] = {0b010, 0b110, 0b010, 0b010, 2};
    const uint8_t tiny2[] = {0b111, 0b001, 0b110, 0b111, 3};
    const uint8_t tiny3[] = {0b111, 0b011, 0b011, 0b111, 3}; // hmm
    const uint8_t tiny4[] = {0b101, 0b101, 0b111, 0b001, 3};
    const uint8_t tiny5[] = {0b111, 0b110, 0b001, 0b111, 3};
    const uint8_t tiny6[] = {0b100, 0b110, 0b101, 0b111, 3};
    const uint8_t tiny7[] = {0b111, 0b001, 0b010, 0b100, 3};
    const uint8_t tiny8[] = {0b111, 0b101, 0b010, 0b111, 3}; // hmm, very hmm
    const uint8_t tiny9[] = {0b111, 0b101, 0b111, 0b001, 3};

// special chars:
    const uint8_t tiny_[] = {0b000, 0b000, 0b000, 0b000, 3};
    const uint8_t tiny_1[] = {0b000, 0b000, 0b000, 0b000, 1};
    const uint8_t tiny_2[] = {0b000, 0b000, 0b000, 0b000, 2};

    const uint8_t tinyUnderscore[] = {0b000, 0b000, 0b000, 0b111, 3};
    const uint8_t tinyPipe[] = {0b010, 0b010, 0b010, 0b010, 1};

    const uint8_t tinyRoundBracketO[] = {0b010, 0b100, 0b100, 0b010, 2};
    const uint8_t tinyRoundBracketC[] = {0b100, 0b010, 0b010, 0b100, 2};

    const uint8_t tinySquareBracketO[] = {0b110, 0b100, 0b100, 0b110, 2}; // very similar to C
    const uint8_t tinySquareBracketC[] = {0b110, 0b010, 0b010, 0b110, 2};

    const uint8_t tinyDot[] = {0b000, 0b000, 0b000, 0b100, 1};
    const uint8_t tinyComma[] = {0b000, 0b000, 0b010, 0b100, 2};
    const uint8_t tinyQuestionMark[] = {0b111, 0b011, 0b000, 0b010, 3}; // hmm
    const uint8_t tinyExclamationMark[] = {0b100, 0b100, 0b000, 0b100, 1}; // hmm

    const uint8_t tinyDash[] = {0b000, 0b000, 0b111, 0b000, 3};
    const uint8_t tinyColon[] = {0b100, 0b000, 0b100, 0b000, 1};
    const uint8_t tinySemiColon[] = {0b010, 0b000, 0b010, 0b100, 3};

    const uint8_t tinyPlus[] = {0b000, 0b010, 0b111, 0b010, 3};
    const uint8_t tinySlash[] = {0b001, 0b010, 0b010, 0b100, 3};
    const uint8_t tinyBackSlash[] = {0b100, 0b010, 0b010, 0b001, 3};


    const uint8_t breakChar[] = {0x00, 0x00, 0x00, 0x00, 0};


    const std::string tinyNormalChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 0123456789().,?!_-:[];+/\\";
    const std::string tinySpecialChars = "12l|n";

    const uint16_t SINGLE_SPACE_INDEX = tinySpecialChars.find('1') + tinyNormalChars.length();

    const uint16_t breakCharSpecialIndex = tinySpecialChars.find('n');


    const uint8_t *tinyLetter[] = {tinyA, tinyB, tinyC, tinyD, tinyE, tinyF, tinyG, tinyH, tinyI, tinyJ, tinyK,
                                          tinyL, tinyM, tinyN, tinyO, tinyP, tinyQ, tinyR, tinyS, tinyT, tinyU,
                                          tinyV, tinyW, tinyX, tinyY, tinyZ,
                                          tinyA, tinyB, tinyC, tinyD, tinyE, tinyF, tinyG, tinyH, tinyI, tinyJ, tinyK,
                                          tinyL, tinyM, tinyN, tinyO, tinyP, tinyQ, tinyR, tinyS, tinyT, tinyU,
                                          tinyV, tinyW, tinyX, tinyY, tinyZ,
                                          tiny_, tiny0, tiny1, tiny2, tiny3, tiny4, tiny5, tiny6, tiny7, tiny8, tiny9,
                                          tinyRoundBracketO, tinyRoundBracketC, tinyDot, tinyComma, tinyQuestionMark,
                                          tinyExclamationMark, tinyUnderscore,
                                          tinyDash, tinyColon, tinySquareBracketO, tinySquareBracketC, tinySemiColon,
                                          tinyPlus, tinySlash, tinyBackSlash,

                                          tiny_1, tiny_2, tinyPipe, tinyPipe, breakChar};

}

