//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_TEXTCONTROLLER_CHARSET_H
#define TGL_BOARD_TEXTCONTROLLER_CHARSET_H

#include "letters.h"
#include "tiny_letters.h"

struct Charset{
    const uint8_t charHeight; // Same as length index-1 (So length index = charHeight +1)
    const uint8_t **chars;
    const uint16_t *singleSpaceIndex;

};

inline const Charset normalLetters{8, details_letters_normal::Letter, &details_letters_normal::SINGLE_SPACE_INDEX};
inline const Charset tinyLetters{4, details_letters_tiny::tinyLetter, &details_letters_tiny::SINGLE_SPACE_INDEX};









#endif //TGL_BOARD_TEXTCONTROLLER_CHARSET_H
