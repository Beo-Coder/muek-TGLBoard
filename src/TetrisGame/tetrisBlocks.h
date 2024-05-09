//
// Created by thijs on 08.05.24.
//

#ifndef TETRIS_TETRISBLOCKS_H
#define TETRIS_TETRISBLOCKS_H

#include "color.h"


static bool pieceI[4][4] = {{1,1,1,1},
                     {0,0,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};
static bool pieceJ[4][4] = {{1,0,0,0},
                     {1,1,1,0},
                     {0,0,0,0},
                     {0,0,0,0}};
static bool pieceL[4][4] = {{0,0,1,0},
                     {1,1,1,0},
                     {0,0,0,0},
                     {0,0,0,0}};
static bool pieceO[4][4] = {{1,1,0,0},
                     {1,1,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};
static bool pieceS[4][4] = {{0,1,1,0},
                     {1,1,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};
static bool pieceT[4][4] = {{1,1,1,0},
                     {0,1,0,0},
                     {0,0,0,0},
                     {0,0,0,0}};
static bool pieceZ[4][4] = {{1,1,0,0},
                     {0,1,1,0},
                     {0,0,0,0},
                     {0,0,0,0}};

#define BLOCK_COUNT 8
static bool (*blocks[BLOCK_COUNT])[4][4] = {&pieceI, &pieceJ, &pieceL, &pieceO, &pieceS, &pieceT, &pieceT, &pieceZ};


static Color slightlyRed(0.125, 0, 0);
static Color overlayWhite(0.5, 0.5, 0.5);
static Color colorOrange(1, 0.5, 0);
// we don't want white so... allColors without white
#define COLOR_COUNT 6
static Color *blockColors[COLOR_COUNT] = {&colorBlue, &colorCyan, &colorGreen, &colorPurple, &colorRed, &colorYellow};

#define TIER_COLOR_COUNT 7

static Color *tierColors[TIER_COLOR_COUNT] = {&colorWhite, &colorGreen, &colorYellow, &colorOrange, &colorRed, &colorBlue, &colorPurple};


#endif //TETRIS_TETRISBLOCKS_H
