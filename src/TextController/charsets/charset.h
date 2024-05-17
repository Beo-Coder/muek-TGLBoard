//
// Created by leo on 17.05.24.
//

#ifndef MUEK_TGL_BOARD2_CHARSET_H
#define MUEK_TGL_BOARD2_CHARSET_H

#include "letters.h"
#include "tiny_letters.h"

struct Charset{
    uint8_t charHeight; // Same as length index-1 (So length index = charHeight +1)
    const uint8_t **chars;
    uint16_t singleSpaceIndex;

};

static Charset normalLetters{8, details_letters_normal::Letter, details_letters_normal::SINGLE_SPACE_INDEX};
static Charset tinyLetters{4, details_letters_tiny::tinyLetter, details_letters_tiny::SINGLE_SPACE_INDEX};








#endif //MUEK_TGL_BOARD2_CHARSET_H
