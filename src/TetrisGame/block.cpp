//
// Created by thijs on 08.05.24.
//

#include "block.h"

void Block::translateBlockToColor() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            colorArray[i][j] = blockArray[i][j] ? *color : colorBlank;
        }
    }
}

Block::Block(bool (*blockArray)[4][4], Color *color) {
    this->color = color;
    // let's copy the array ...
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->blockArray[i][j] = (*blockArray)[i][j];
        }
    }
    translateBlockToColor();
}

Color (*Block::getColorArray())[4][4] {
    return &colorArray;
}

bool (*Block::getBlockArray())[4][4] {
    return &blockArray;
}

int Block::getLengthInColumn(int col) { // returns the row on which the piece would technically collide at the desired column(0 = no collision)
    int colCount = 0;

    for (int i = 0; i < 4; ++i) {
        if (blockArray[i][col]) {
            colCount = i + 1;
        }
    }

    return colCount;
}

void Block::rotateBlock() { // always clockwise
    // buffer
    bool bufferArr[4][4];
    int rotationRow = 3;

    // calculate rotated matrix
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = rotationRow - i;
            if (x >= 0 && x <= 3) {
                bufferArr[j][x] = blockArray[i][j];
            }
        }
    }

    // push block to left upper corner to prevent disadvantages
    int firstFilledRow = 0;
    bool rowNotEmpty = false;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            rowNotEmpty |= bufferArr[i][j];
        }
        if (!rowNotEmpty) {
            firstFilledRow++;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i + firstFilledRow <= 3) {
                bufferArr[i][j] = bufferArr[i+firstFilledRow][j];
            } else {
                bufferArr[i][j] = false;
            }

        }
    }

    // push to the left
    int firstFilledCol = 0;
    bool colNotEmpty = false;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            colNotEmpty |= bufferArr[j][i];
        }
        if (!colNotEmpty) {
            firstFilledCol++;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (j + firstFilledCol <= 3) {
                bufferArr[i][j] = bufferArr[i][j + firstFilledCol];
            } else {
                bufferArr[i][j] = false;
            }
        }
    }

    // overwrite old matrix and update values
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            blockArray[i][j] = bufferArr[i][j];
        }
    }

    translateBlockToColor();

    rotation = (rotation + 1) % 4; // set the rotation value

}
