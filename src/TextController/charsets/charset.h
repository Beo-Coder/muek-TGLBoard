//
// Created by leo on 17.05.24.
//

#ifndef TGL_BOARD_TEXTCONTROLLER_CHARSET_H
#define TGL_BOARD_TEXTCONTROLLER_CHARSET_H

#include "letters.h"
#include "tiny_letters.h"

struct Charset{
    uint8_t charHeight; // Same as length index-1 (So length index = charHeight +1)
    const uint8_t **chars;
    uint16_t singleSpaceIndex;

};

extern Charset normalLetters;
extern Charset tinyLetters;








#endif //TGL_BOARD_TEXTCONTROLLER_CHARSET_H
