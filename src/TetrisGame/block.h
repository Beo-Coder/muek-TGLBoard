//
// Created by thijs on 08.05.24.
//

#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include "color.h"

class Block {
private:
    Color *color;
    int rotation = 0;
    bool blockArray[4][4] = {};
    Color colorArray[4][4] = {};

    void translateBlockToColor();
public:
    Block(bool (*blockArray)[4][4], Color *color);
    Color (*getColorArray())[4][4];
    bool (*getBlockArray())[4][4];

    void rotateBlock();

    int getLengthInColumn(int col);
};


#endif //TETRIS_BLOCK_H
