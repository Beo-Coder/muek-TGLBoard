//
// Created by leo on 03.03.24.
//

#ifndef TGL_BOARD_TEXTCONTROLLER_LETTERS_H
#define TGL_BOARD_TEXTCONTROLLER_LETTERS_H

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include <string>

namespace details_letters_normal {


// Capital letters
    inline const uint8_t lA[] = {0b00100, 0b01010, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001, 0b10001, 5}; // A
    inline const uint8_t lB[] = {0b11110, 0b10001, 0b10001, 0b11110, 0b10001, 0b10001, 0b10001, 0b11110, 5}; // B
    inline const uint8_t lC[] = {0b01110, 0b10001, 0b10000, 0b10000, 0b10000, 0b10000, 0b10001, 0b01110, 5}; // C
    inline const uint8_t lD[] = {0b11110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b11110, 5}; // D
    inline const uint8_t lE[] = {0b11111, 0b10000, 0b10000, 0b11110, 0b10000, 0b10000, 0b10000, 0b11111, 5}; // E
    inline const uint8_t lF[] = {0b11111, 0b10000, 0b10000, 0b11110, 0b10000, 0b10000, 0b10000, 0b10000, 5}; // F
    inline const uint8_t lG[] = {0b01110, 0b10001, 0b10000, 0b10000, 0b10111, 0b10001, 0b10001, 0b01110, 5}; // G
    inline const uint8_t lH[] = {0b10001, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001, 0b10001, 5}; // H
    inline const uint8_t lI[] = {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b11111, 5}; // I
    inline const uint8_t lJ[] = {0b11111, 0b00010, 0b00010, 0b00010, 0b00010, 0b00010, 0b10010, 0b01100, 5}; // J
    inline const uint8_t lK[] = {0b10001, 0b10010, 0b10100, 0b11000, 0b10100, 0b10010, 0b10001, 0b10001, 5}; // K
    inline const uint8_t lL[] = {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b11111, 5}; // L
    inline const uint8_t lM[] = {0b10001, 0b11011, 0b10101, 0b10101, 0b10001, 0b10001, 0b10001, 0b10001, 5}; // M
    inline const uint8_t lN[] = {0b10001, 0b10001, 0b11001, 0b10101, 0b10011, 0b10001, 0b10001, 0b10001, 5}; // N
    inline const uint8_t lO[] = {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 5}; // O
    inline const uint8_t lP[] = {0b11110, 0b10001, 0b10001, 0b11110, 0b10000, 0b10000, 0b10000, 0b10000, 5}; // P
    inline const uint8_t lQ[] = {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10101, 0b10010, 0b01101, 5}; // Q
    inline const uint8_t lR[] = {0b11110, 0b10001, 0b10001, 0b11110, 0b10010, 0b10001, 0b10001, 0b10001, 5}; // R
    inline const uint8_t lS[] = {0b01110, 0b10001, 0b10000, 0b01110, 0b00001, 0b00001, 0b10001, 0b01110, 5}; // S
    inline const uint8_t lT[] = {0b11111, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 5}; // T
    inline const uint8_t lU[] = {0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 5}; // U
    inline const uint8_t lV[] = {0b10001, 0b10001, 0b10001, 0b10001, 0b01010, 0b01010, 0b00100, 0b00100, 5}; // V
    inline const uint8_t lW[] = {0b10001, 0b10001, 0b10001, 0b10101, 0b10101, 0b11011, 0b11011, 0b10001, 5}; // W
    inline const uint8_t lX[] = {0b10001, 0b10001, 0b01010, 0b00100, 0b00100, 0b01010, 0b10001, 0b10001, 5}; // X
    inline const uint8_t lY[] = {0b10001, 0b10001, 0b01010, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 5}; // Y
    inline const uint8_t lZ[] = {0b11111, 0b00001, 0b00010, 0b00100, 0b01000, 0b10000, 0b10000, 0b11111, 5}; // Z

// Small letters
    inline const uint8_t la[] = {0b00000, 0b00000, 0b01110, 0b00001, 0b01111, 0b10001, 0b10001, 0b01111, 5}; // a
    inline const uint8_t lb[] = {0b10000, 0b10000, 0b10000, 0b11110, 0b10001, 0b10001, 0b10001, 0b11110, 5}; // b
    inline const uint8_t lc[] = {0b00000, 0b00000, 0b00111, 0b01000, 0b01000, 0b01000, 0b01000, 0b00111, 4}; // c
    inline const uint8_t ld[] = {0b00001, 0b00001, 0b00001, 0b01111, 0b10001, 0b10001, 0b10001, 0b01111, 5}; // d
    inline const uint8_t le[] = {0b00000, 0b00000, 0b01110, 0b10001, 0b11111, 0b10000, 0b10001, 0b01110, 5}; // e
    inline const uint8_t lf[] = {0b00011, 0b00100, 0b00100, 0b01110, 0b00100, 0b00100, 0b00100, 0b00100, 4}; // f
    inline const uint8_t lg[] = {0b00000, 0b00000, 0b01111, 0b10001, 0b10001, 0b01111, 0b00001, 0b01110, 5}; // g
    inline const uint8_t lh[] = {0b10000, 0b10000, 0b10000, 0b11110, 0b10001, 0b10001, 0b10001, 0b10001, 5}; // h
    inline const uint8_t li[] = {0b00000, 0b00001, 0b00000, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 1}; // i
    inline const uint8_t lj[] = {0b00000, 0b00001, 0b00000, 0b00001, 0b00001, 0b00001, 0b01001, 0b00110, 2}; // j
    inline const uint8_t lk[] = {0b01000, 0b01000, 0b01001, 0b01010, 0b01100, 0b01100, 0b01010, 0b01001, 4}; // k
    inline const uint8_t ll[] = {0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00011, 3}; // l
    inline const uint8_t lm[] = {0b00000, 0b00000, 0b11110, 0b10101, 0b10101, 0b10101, 0b10101, 0b10101, 5}; // m
    inline const uint8_t ln[] = {0b00000, 0b00000, 0b11110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 5}; // n
    inline const uint8_t lo[] = {0b00000, 0b00000, 0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 5}; // o
    inline const uint8_t lp[] = {0b00000, 0b00000, 0b11110, 0b10001, 0b10001, 0b11110, 0b10000, 0b10000, 5}; // p
    inline const uint8_t lq[] = {0b00000, 0b00000, 0b01111, 0b10001, 0b10001, 0b01111, 0b00001, 0b00001, 5}; // q
    inline const uint8_t lr[] = {0b00000, 0b00000, 0b11110, 0b10001, 0b10000, 0b10000, 0b10000, 0b10000, 5}; // r
    inline const uint8_t ls[] = {0b00000, 0b00000, 0b01111, 0b10000, 0b01110, 0b00001, 0b10001, 0b01110, 5}; // s
    inline const uint8_t lt[] = {0b00100, 0b00100, 0b00100, 0b01110, 0b00100, 0b00100, 0b00100, 0b00011, 4}; // t
    inline const uint8_t lu[] = {0b00000, 0b00000, 0b00000, 0b10001, 0b10001, 0b10001, 0b10001, 0b01111, 5}; // u
    inline const uint8_t lv[] = {0b00000, 0b00000, 0b10001, 0b10001, 0b10001, 0b01010, 0b01010, 0b00100, 5}; // v
    inline const uint8_t lw[] = {0b00000, 0b00000, 0b10001, 0b10001, 0b10101, 0b10101, 0b11011, 0b10001, 5}; // w
    inline const uint8_t lx[] = {0b00000, 0b00000, 0b10001, 0b01010, 0b00100, 0b01010, 0b10001, 0b00000, 5}; // x
    inline const uint8_t ly[] = {0b00000, 0b00000, 0b10001, 0b10001, 0b10001, 0b01111, 0b00001, 0b11110, 5}; // y
    inline const uint8_t lz[] = {0b00000, 0b00000, 0b11111, 0b00010, 0b00100, 0b01000, 0b10000, 0b11111, 5}; // z

// Numbers

    inline const uint8_t l0[] = {0b01110, 0b10001, 0b10011, 0b10101, 0b10101, 0b11001, 0b10001, 0b01110, 5}; // 0
// inline const uint8_t l1[] = {0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110, 5}; // 1; 5 Pixel wide
    inline const uint8_t l1[] = {0b00010, 0b00110, 0b00010, 0b00010, 0b00010, 0b00010, 0b00010, 0b00111,
                          3}; // 1; 3 Pixel wide
    inline const uint8_t l2[] = {0b01110, 0b10001, 0b00001, 0b00010, 0b00100, 0b01000, 0b10000, 0b11111, 5}; // 2
    inline const uint8_t l3[] = {0b11111, 0b00001, 0b00010, 0b00100, 0b00010, 0b00001, 0b10001, 0b01110, 5}; // 3
    inline const uint8_t l4[] = {0b00010, 0b00110, 0b01010, 0b10010, 0b11111, 0b00010, 0b00010, 0b00010, 5}; // 4
    inline const uint8_t l5[] = {0b11111, 0b10000, 0b10000, 0b11110, 0b00001, 0b00001, 0b10001, 0b01110, 5}; // 5
    inline const uint8_t l6[] = {0b01110, 0b10001, 0b10000, 0b11110, 0b10001, 0b10001, 0b10001, 0b01110, 5}; // 6
    inline const uint8_t l7[] = {0b11111, 0b00001, 0b00010, 0b00100, 0b00100, 0b01000, 0b01000, 0b01000, 5}; // 7
    inline const uint8_t l8[] = {0b01110, 0b10001, 0b10001, 0b01110, 0b10001, 0b10001, 0b10001, 0b01110, 5}; // 8
    inline const uint8_t l9[] = {0b01110, 0b10001, 0b10001, 0b01111, 0b00001, 0b00001, 0b10001, 0b01110, 5}; // 9

// Other chars
    inline const uint8_t l_[] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
                          5}; // Space (5 pixels wide)

    inline const uint8_t l_0[] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
                           0}; // Space (0 pixel wide) Only for special things

    inline const uint8_t l_1[] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
                           1}; // Space (1 pixel wide)
    inline const uint8_t l_2[] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
                           2}; // Space (2 pixels wide)
    inline const uint8_t l_3[] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
                           3}; // Space (3 pixels wide)
    inline const uint8_t l_4[] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
                           4}; // Space (4 pixels wide)

    inline const uint8_t lLine[] = {0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 1}; // Line (1 pixel wide)


    inline const uint8_t lAe[] = {0b10001, 0b00100, 0b01010, 0b10001, 0b11111, 0b10001, 0b10001, 0b10001, 5}; // Ä
    inline const uint8_t lOe[] = {0b10001, 0b00000, 0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 5}; // Ö
    inline const uint8_t lUe[] = {0b10001, 0b00000, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 5}; // Ü

    inline const uint8_t lae[] = {0b01001, 0b00000, 0b01110, 0b00001, 0b01111, 0b10001, 0b10001, 0b01111, 5}; // ä
    inline const uint8_t loe[] = {0b10001, 0b00000, 0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 5}; // ö
    inline const uint8_t lue[] = {0b00000, 0b10001, 0b00000, 0b10001, 0b10001, 0b10001, 0b10001, 0b01111, 5}; // ü


    inline const uint8_t roundBracketO2[] = {0b0011, 0b0110, 0b1100, 0b1100, 0b1100, 0b1100, 0b0110, 0b0011, 4}; // (
    inline const uint8_t roundBracketC2[] = {0b1100, 0b0110, 0b0011, 0b0011, 0b0011, 0b0011, 0b0110, 0b1100, 4}; // )


    inline const uint8_t roundBracketO1[] = {0b011, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b011, 3}; // (
    inline const uint8_t roundBracketC1[] = {0b110, 0b001, 0b001, 0b001, 0b001, 0b001, 0b001, 0b110, 3}; // )

    inline const uint8_t squareBracketO[] = {0b111, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b111, 3}; // [
    inline const uint8_t squareBracketC[] = {0b111, 0b001, 0b001, 0b001, 0b001, 0b001, 0b001, 0b111, 3}; // ]


    inline const uint8_t curlyBracketO[] = {0b0011, 0b0100, 0b0100, 0b1100, 0b1100, 0b0100, 0b0100, 0b0011, 4}; // {
    inline const uint8_t curlyBracketC[] = {0b1100, 0b0010, 0b0010, 0b0011, 0b0011, 0b0010, 0b0010, 0b1100, 4}; // }


    inline const uint8_t angleBracketO[] = {0b000, 0b001, 0b010, 0b100, 0b100, 0b010, 0x001, 0x000, 3}; // <
    inline const uint8_t angleBracketC[] = {0b000, 0b100, 0b010, 0b001, 0b001, 0b010, 0b100, 0b000, 3}; // >


    inline const uint8_t lDot[] = {0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b11, 0b11, 2}; // .
    inline const uint8_t lComma[] = {0b00, 0b00, 0b00, 0b00, 0b11, 0b11, 0b01, 0b10, 2}; // ,
    inline const uint8_t lQuestionMark[] = {0b001110, 0b10001, 0b10001, 0b00010, 0b00100, 0b00100, 0b00000, 0b00100,
                                     5}; // ?
    inline const uint8_t lExclamationMark[] = {0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00000, 0b00001,
                                        1};

    inline const uint8_t lUnderscore[] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
                                   0b11111, 5}; // _
    inline const uint8_t lDash[] = {0b000, 0b000, 0b000, 0b000, 0b0111, 0b000, 0b000, 0b000, 3}; // -
    inline const uint8_t lColon[] = {0b0, 0b0, 0b0, 0b1, 0b0, 0b0, 0b1, 0b0, 1}; // :
    inline const uint8_t lSemicolon[] = {0b00, 0b00, 0b00, 0b01, 0b00, 0b00, 0b01, 0b10, 2}; // ;




// Special chars

    inline const uint8_t heart[] = {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000,
                             0b00000000, 8}; // <3
    inline const uint8_t smileCircle[] = {0b00111100, 0b01000010, 0b10100101, 0b10000001, 0b10100101, 0b10011001,
                                   0b01000010,
                                   0b00111100, 8}; // :)






    inline const  std::string normalChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 0123456789().,?!_-:[]{}<>;";
    inline const  std::string specialChars = "HS01234l|AaOoUu()";

    // Gets stored in ROM
    inline const uint16_t SINGLE_SPACE_INDEX = specialChars.find('1') + normalChars.length();

    inline const uint8_t *Letter[] = {lA, lB, lC, lD, lE, lF, lG, lH, lI, lJ, lK, lL, lM, lN, lO, lP, lQ, lR, lS, lT,
                               lU,
                               lV, lW, lX, lY, lZ, la, lb, lc, ld, le, lf, lg, lh, li, lj, lk, ll, lm, ln, lo,
                               lp,
                               lq, lr, ls, lt, lu, lv, lw, lx, ly, lz, l_, l0, l1, l2, l3, l4, l5, l6, l7, l8,
                               l9,
                               roundBracketO1, roundBracketC1, lDot, lComma, lQuestionMark, lExclamationMark,
                               lUnderscore,
                               lDash, lColon, squareBracketO, squareBracketC, curlyBracketO, curlyBracketC,
                               angleBracketO, angleBracketC, lSemicolon,

                               heart, smileCircle, l_0, l_1, l_2, l_3, l_4, lLine, lLine, lAe, lae, lOe, loe,
                               lUe, lue, roundBracketO2, roundBracketC2};

}
#endif //TGL_BOARD_TEXTCONTROLLER_LETTERS_H
