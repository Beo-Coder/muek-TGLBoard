//
// Created by thijs on 08.05.24.
//

#include "tetris.h"
#include "tetrisBlocks.h"
#include <hardware/structs/rosc.h>
#include "TextController/text_controller.h"
#include "block.h"
#include "beo_common.h"


// pick random block
// put it at top
// let it fall
// as soon as we touch something stop the block
// repeat
void Tetris::reset() {
    scheduleRotation = false;
    loss = false;
    score = 0;
    prevMillis = beo::millis();
    prevScrollMillis = beo::millis();
    // empty arrays and frame
    clearFrame();
    for (int i = 0; i < MATRIX_HEIGHT; ++i) {
        for (int j = 0; j < MATRIX_LENGTH; ++j) {
            map[i][j] = false;
            colorMap[i][j] = &colorBlank;
        }
    }
    
    // create first block (resets x and y and flying block)
    generateNewBlock();
    tickCnt = 0;
}

void Tetris::loop() {
    uint32_t currentMillis = beo::millis();
    if (loss && currentMillis - prevScrollMillis >= SCORE_TEXT_SCROLL_SPEED) {

        textController->createAndLoadFrame();

        prevScrollMillis = currentMillis;
    }
    if (currentMillis - prevMillis >= frameSpeed) { // update display
        graphicTick();

    }

    if (currentMillis - prevMillis >= tickSpeed && !loss) { // update game
        tick();

        prevMillis = currentMillis;
    }


    if (loss && currentMillis - prevMillis >= LOSS_DELAY) {
        reset();
    }

}

void Tetris::tick() {
    if(detectCollision()) {
        mergeBlockIntoMap();
        detectAndDeleteRow();
        generateNewBlock();
        detectLoss(); // after row deletion to give the player one last chance, although it won't help much
    }


    blockY++; // move block down
    tickCnt++; // increment tick
}

void Tetris::graphicTick() {
    if (!loss) {
        handleScheduledActions();
        copyMapIntoDisplay();
        mergeBlockIntoDisplay();
        mergeOverlayIntoDisplay();
        matrix->setDisplayData(frame);
    }

    matrix->sendData();
}

void Tetris::handleScheduledActions() {
    // handle rotation
    if (scheduleRotation) {
        scheduleRotation = false;

        flyingBlock->rotateBlock();

        // we might need to push the block to the left, back into the screen:
        int width = 4;
        bool inColumn = false;
        for (int i = 3; i >= 0; --i) {
            for (int j = 0; j < 4; ++j) {
                inColumn |= (*flyingBlock->getBlockArray())[j][i];
            }

            if (!inColumn) {
                width--;
            }

        }

        if (blockX + width > MATRIX_HEIGHT) {
            blockX = MATRIX_HEIGHT - width;
        }

        // we might want to forbid the rotation if it collides with other blocks or goes into the ground
        // -> quick fix: just rotate it 3 more times (not the best solution, but it works)
        bool forbidRotation = false;
        for (int x = 0; x < 4; ++x) {
            for (int y = 0; y < 4; ++y) {
                int checkX = MATRIX_HEIGHT - 1 - (blockX + x);
                if (checkX <= MATRIX_HEIGHT -1 && blockY + y <= MATRIX_LENGTH -1) { // check for collision with other blocks
                    forbidRotation |= (*flyingBlock->getBlockArray())[y][x] && map[checkX][blockY + y];
                }
                if (blockY + y >= MATRIX_LENGTH && (*flyingBlock->getBlockArray())[y][x]) { // check for collision with ground
                    forbidRotation |= true;
                }
            }
        }

        if (forbidRotation) { // cancel rotation
            flyingBlock->rotateBlock();
            flyingBlock->rotateBlock();
            flyingBlock->rotateBlock();
        }

    }
}

Tetris::Tetris(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], TextController *scrollController) : display_program(ledMatrix, frame) {
    /* redundant happens in display_program constructor already
    this->matrix = ledMatrix;
    this->frame = frame;
    */
    // reset(); // already done in main.cpp
    this->textController = scrollController;
    refreshSpeed = frameSpeed; // we would actually prefer no delay but if we must...

}

void Tetris::copyMapIntoDisplay() {
    // copy the current map
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 16; ++j) {
            (*frame)[i][j] = *colorMap[i][j];
        }
    }
}

void Tetris::mergeBlockIntoDisplay() {
    // overlay the frame with a block at coordinates blockX and blockY
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // keep in mind that blocks are moving from left to right therefore we rotate the coordinates

            int actualY = MATRIX_HEIGHT - 1 - (blockX + i);
            if (actualY >= 0 && actualY <= 7) {
                if ((*frame)[actualY][blockY + j].equals(&colorBlank)) {
                    (*frame)[actualY][blockY + j] = *(*flyingBlock->getColorArray())[j][i];
                }
            }

        }
    }
}

void Tetris::mergeBlockIntoMap() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // rotate the coords (same as merge into display)
            int actualY = MATRIX_HEIGHT - 1 - (blockX + i);
            if (actualY >= 0 && actualY <= 7) {

                map[actualY][blockY + j] |= (*flyingBlock->getBlockArray())[j][i];
                if ((*flyingBlock->getBlockArray())[j][i]) {
                    colorMap[actualY][blockY + j] = (*flyingBlock->getColorArray())[j][i];
                }
            }
        }
    }
}

bool Tetris::detectCollision() {
    // check every column of currently flying block
    for (int i = 0; i < 4; ++i) {
        int lengthInCol = flyingBlock->getLengthInColumn(i);
        if (lengthInCol != 0) {
            int checkX = MATRIX_HEIGHT - 1 - (blockX + i);
            int checkY = blockY + lengthInCol;
            if (checkY >= MATRIX_LENGTH) return true;
            if (map[checkX][checkY]) return true;
        }
    }

    return false;
}

void Tetris::generateNewBlock() {
    uint32_t randomBlockIndex = genRandomNumber(BLOCK_COUNT - 1);
    uint32_t randomColorIndex = genRandomNumber(COLOR_COUNT - 1);

    delete flyingBlock;
    flyingBlock = new Block(blocks[randomBlockIndex], blockColors[randomColorIndex]);

    blockX = START_X;
    blockY = START_Y;
}

uint32_t Tetris::genRandomNumber(int max) {
    uint32_t random;
    for (int i = 0; i < 4*8; ++i) { // 4 bytes
        random |= rosc_hw->randombit;
        random = random << 1;
    }
    return (random % max);
}

void Tetris::moveLeft() {

    // check if we would collide

    bool allowMove = true;
    for (int i = 0; i < 4; ++i) {
        int widthOnRow = 4;
        for (int j = 3; j >= 0; --j) {
            if ((*flyingBlock->getBlockArray())[i][j]) {
                widthOnRow = j;
            }
        }

        if (widthOnRow != 4) {
            int checkX = MATRIX_HEIGHT - 1 - (blockX - 1 + widthOnRow);
            if (checkX >= 0) {
                if (map[checkX][blockY + i] && (*flyingBlock->getBlockArray())[i][0]) {
                    allowMove = false;
                }
            }
        }

    }

    if (blockX - 1 >= 0 && allowMove) {
        blockX--;
    }
}

void Tetris::moveRight() {
    // find out how far we are sticking out to the right
    int width = 4;
    bool inColumn = false;
    for (int i = 3; i >= 0; --i) {
        for (int j = 0; j < 4; ++j) {
            inColumn |= (*flyingBlock->getBlockArray())[j][i];
        }

        if (!inColumn) {
            width--;
        }

    }

    // check if we are moving into another block

    bool allowMove = true;
    for (int i = 0; i < 4; ++i) {
        int widthOnRow = 0;
        for (int j = 0; j < 4; ++j) {
            if ((*flyingBlock->getBlockArray())[i][j]) {
                widthOnRow = j+1;
            }
        }
        // check if collision is imminent
        int checkX = MATRIX_HEIGHT - 1 - (blockX + widthOnRow);
        if (checkX <= 7) {
            if (widthOnRow != 0 && map[checkX][blockY + i]) {
                allowMove = false;
            }
        }

    }

    if (blockX + width <= MATRIX_HEIGHT - 1 && allowMove) {
        blockX++;
    }
}

void Tetris::rotate() {
    // rotation acts with non-volatile vars so we schedule it
    scheduleRotation = true;
}

void Tetris::detectAndDeleteRow() {
    for (int i = 0; i < MATRIX_LENGTH; ++i) {
        bool rowComplete = true;
        for (int j = 0; j < MATRIX_HEIGHT; ++j) {
            if (!map[j][i]) { // we turn around the display by 90° therefore swap
                rowComplete = false;
            }
        }

        if (rowComplete) {
            // remove row
            for (int j = 0; j < i; ++j) { // row 0 cant get a replacement
                for (int k = 0; k < MATRIX_HEIGHT; ++k) {
                    map[k][i-j] = map[k][i-j-1]; // get row above current row and copy it over
                    colorMap[k][i-j] = colorMap[k][i-j-1];
                }
            }
            score++; // increase score
        }
    }



}

void Tetris::detectLoss() {
    // as soon as a block embeds itself into the map at y = 2 -> game over
    for (int i = 0; i < MATRIX_HEIGHT; ++i) {
        if (map[i][LOSS_Y]) {
            loss |= true;
            // prepare score display
            textController->restart();
            textController->setColor(&overlayWhite, &slightlyRed);
            stringBuffer = "";
            stringBuffer.append(std::to_string(score));
            textController->setText(&stringBuffer);
            textController->createAndLoadFrame();


        }
    }
}

void Tetris::mergeOverlayIntoDisplay() {
    // generate bar at top of field
    for (int i = 0; i < MATRIX_HEIGHT; ++i) {
        (*frame)[i][2].add(&overlayWhite);
    }
    // generate binary counter score
    // if someone has too much time... here you go if you manage to overflow 2^MATRIX_HEIGHT:

    unsigned int overFlowBits = score >> MATRIX_HEIGHT;

    for (int i = 0; i < MATRIX_HEIGHT; ++i) {

        if (overFlowBits < TIER_COLOR_COUNT) {
            Color modifiedColor(0,0,0);

            modifiedColor.set(tierColors[overFlowBits]);
            modifiedColor.multiply(1);
            (*frame)[i][0] = (score >> i) % 2 ? modifiedColor : colorBlank;

        } else {
            // just spam colors in list order if someone does somehow reach 2^MATRIX_HEIGHT * TIER_COLOR_COUNT
            (*frame)[i][0] = *tierColors[tickCnt % TIER_COLOR_COUNT];
        }
    }

}

void Tetris::refresh() {
    this->loop();
}

void Tetris::restart() {
    this->reset();
}

void Tetris::button1ISR(bool data) {
    if (!data) { // falling edge
        if (!rotated) {
            moveLeft();
        } else {
            rotated = false;
        }
    }
    button1Cache = data;
}

void Tetris::button2ISR(bool data) {
    if (data) { // rising edge
        if (button1Cache) { // rising edge whilst select is pressed
            rotated = true;
            rotate();
        }
    }
    if (!data) { // falling edge
        if (!rotated) {
            moveRight();
        }
        // don't reset rotated because we did not yet release the select button

    }

    button2Cache = data;
}







