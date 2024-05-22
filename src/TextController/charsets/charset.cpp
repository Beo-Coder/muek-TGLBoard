//
// Created by leo on 21.05.24.
//
#include "charset.h"


Charset normalLetters{8, details_letters_normal::Letter, &details_letters_normal::SINGLE_SPACE_INDEX};
Charset tinyLetters{4, details_letters_tiny::tinyLetter, &details_letters_tiny::SINGLE_SPACE_INDEX};