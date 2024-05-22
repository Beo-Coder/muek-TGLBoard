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
    extern const uint8_t lA[]; // A
    extern const uint8_t lB[]; // B
    extern const uint8_t lC[]; // C
    extern const uint8_t lD[]; // D
    extern const uint8_t lE[]; // E
    extern const uint8_t lF[]; // F
    extern const uint8_t lG[]; // G
    extern const uint8_t lH[]; // H
    extern const uint8_t lI[]; // I
    extern const uint8_t lJ[]; // J
    extern const uint8_t lK[]; // K
    extern const uint8_t lL[]; // L
    extern const uint8_t lM[]; // M
    extern const uint8_t lN[]; // N
    extern const uint8_t lO[]; // O
    extern const uint8_t lP[]; // P
    extern const uint8_t lQ[]; // Q
    extern const uint8_t lR[]; // R
    extern const uint8_t lS[]; // S
    extern const uint8_t lT[]; // T
    extern const uint8_t lU[]; // U
    extern const uint8_t lV[]; // V
    extern const uint8_t lW[]; // W
    extern const uint8_t lX[]; // X
    extern const uint8_t lY[]; // Y
    extern const uint8_t lZ[]; // Z

// Small letters
    extern const uint8_t la[]; // a
    extern const uint8_t lb[]; // b
    extern const uint8_t lc[]; // c
    extern const uint8_t ld[]; // d
    extern const uint8_t le[]; // e
    extern const uint8_t lf[]; // f
    extern const uint8_t lg[]; // g
    extern const uint8_t lh[]; // h
    extern const uint8_t li[]; // i
    extern const uint8_t lj[]; // j
    extern const uint8_t lk[]; // k
    extern const uint8_t ll[]; // l
    extern const uint8_t lm[]; // m
    extern const uint8_t ln[]; // n
    extern const uint8_t lo[]; // o
    extern const uint8_t lp[]; // p
    extern const uint8_t lq[]; // q
    extern const uint8_t lr[]; // r
    extern const uint8_t ls[]; // s
    extern const uint8_t lt[]; // t
    extern const uint8_t lu[]; // u
    extern const uint8_t lv[]; // v
    extern const uint8_t lw[]; // w
    extern const uint8_t lx[]; // x
    extern const uint8_t ly[]; // y
    extern const uint8_t lz[]; // z

// Numbers

    extern const uint8_t l0[]; // 0
    extern const uint8_t l1[]; // 1
    extern const uint8_t l2[]; // 2
    extern const uint8_t l3[]; // 3
    extern const uint8_t l4[]; // 4
    extern const uint8_t l5[]; // 5
    extern const uint8_t l6[]; // 6
    extern const uint8_t l7[]; // 7
    extern const uint8_t l8[]; // 8
    extern const uint8_t l9[]; // 9

// Other chars
    extern const uint8_t l_[]; // Space (5 pixels wide)

    extern const uint8_t l_0[]; // Space (0 pixel wide) Only for special things

    extern const uint8_t l_1[]; // Space (1 pixel wide)
    extern const uint8_t l_2[]; // Space (2 pixels wide)
    extern const uint8_t l_3[]; // Space (3 pixels wide)
    extern const uint8_t l_4[]; // Space (4 pixels wide)

    extern const uint8_t lLine[]; // Line (1 pixel wide)


    extern const uint8_t lAe[]; // Ä
    extern const uint8_t lOe[]; // Ö
    extern const uint8_t lUe[]; // Ü

    extern const uint8_t lae[]; // ä
    extern const uint8_t loe[]; // ö
    extern const uint8_t lue[]; // ü


    extern const uint8_t roundBracketO2[]; // (
    extern const uint8_t roundBracketC2[]; // )


    extern const uint8_t roundBracketO1[]; // (
    extern const uint8_t roundBracketC1[]; // )

    extern const uint8_t squareBracketO[]; // [
    extern const uint8_t squareBracketC[]; // ]


    extern const uint8_t curlyBracketO[]; // {
    extern const uint8_t curlyBracketC[]; // }


    extern const uint8_t angleBracketO[]; // <
    extern const uint8_t angleBracketC[]; // >


    extern const uint8_t lDot[]; // .
    extern const uint8_t lComma[]; // ,
    extern const uint8_t lQuestionMark[]; // ?
    extern const uint8_t lExclamationMark[];

    extern const uint8_t lUnderscore[]; // _
    extern const uint8_t lDash[]; // -
    extern const uint8_t lColon[]; // :
    extern const uint8_t lSemicolon[]; // ;




// Special chars

    extern const uint8_t heart[]; // <3
    extern const uint8_t smileCircle[]; // :)


    extern const std::string normalChars;
    extern const std::string specialChars;

    // Gets stored in ROM
    extern const uint16_t SINGLE_SPACE_INDEX;

    extern const uint8_t *Letter[];

}
#endif //TGL_BOARD_TEXTCONTROLLER_LETTERS_H
