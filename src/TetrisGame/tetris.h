//
// Created by thijs on 08.05.24.
//

#ifndef TETRIS_TETRIS_H
#define TETRIS_TETRIS_H

#include "color.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "block.h"
#include "display_program.h"
#include <hardware/structs/rosc.h>

#define SCROLL_SPEED 400
#define LOSS_DELAY 6000
#define START_X 2
#define START_Y 0

#define LOSS_Y 2

class Tetris : public display_program{
public:
    // display program requirements:
    void refresh() override;
    void restart() override;

    void button1ISR(bool data) override; // select
    void button2ISR(bool data) override; // mode


    //explicit Tetris(MatrixOutput* matrix);
    explicit Tetris(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void reset();
    void loop();

    void moveLeft();
    void moveRight();
    void rotate();
//protected:
    //MatrixOutput* matrix; // already in display_program

private:
    bool rotated;
    bool button1Cache;
    bool button2Cache;

    bool loss;
    unsigned int score;

    unsigned int tickCnt;

    Block* flyingBlock;
    volatile int blockX;
    volatile int blockY;
    volatile bool scheduleRotation;


    bool map[MATRIX_HEIGHT][MATRIX_LENGTH] = {};
    Color* colorMap[MATRIX_HEIGHT][MATRIX_LENGTH] = {};

    void copyMapIntoDisplay();
    void mergeBlockIntoDisplay();
    void mergeOverlayIntoDisplay();
    void mergeBlockIntoMap();

    void generateNewBlock();

    bool detectCollision();
    void detectAndDeleteRow();
    void detectLoss();
    static uint32_t genRandomNumber(int max);

    unsigned long prevMillis;
    unsigned int tickSpeed = SCROLL_SPEED;
    unsigned int frameSpeed = 17; // about 60fps

    void tick();
    void graphicTick();
    void handleScheduledActions();


};


#endif //TETRIS_TETRIS_H
