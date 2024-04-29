//
// Created by leo on 27.04.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_FIREWORKANIMATION_H
#define MUEK_ARGB_MATRIX_BOARD_FIREWORKANIMATION_H

#include "Arduino.h"
#include "color.h"
#include "pioMatrixOutput.h"
#include "display_program.h"
#include "BeoCommon.h"

#define SIMULATION_SPEED 220

#define PIXEL_PER_FIREWORK (4*3) // Should be a multiple of 4 (for each direction)
#define PIXEL_PER_FIREWORK_TRAIL 2
#define TIME_DELAY_ARRIVAL_EXPLOSION 1

#define FIREWORK_LIFE_TIME 9
#define TIME_BETWEEN_FIREWORKS 7

#define MAX_NUMBER_FIREWORKS 5

#define FIREWORK_EXPLODE_Y_MIN 4
#define FIREWORK_EXPLODE_Y_MAX 7

// Only Change if you know what you are doing
#define FIREWORK_SPEED_VALUE_X 7 // Value dos not represent real pixel or something
#define FIREWORK_SPEED_VALUE_Y 7 // Value dos not represent real pixel or something

#define FIREWORK_SPEED_VALUE_X2 15 // Value dos not represent real pixel or something
#define FIREWORK_SPEED_VALUE_Y2 15 // Value dos not represent real pixel or something

#define FIREWORK_DECELERATION_VALUE_X 10 // Value dos not represent real pixel or something
#define FIREWORK_DECELERATION_VALUE_Y 10 // Value dos not represent real pixel or something

#define FIREWORK_SINK_RATE (0.01) // Value dos not represent real pixel or something
// End of change only if you know

static Color colorWhite;
static Color colorBla;
static Color colorBla2;
static Color colorBla3;
static Color colorBla4;

static Color colorBlank123;

#define NUMBER_FIREWORK_COLORS 4
static Color *randomColor[] = {&colorBla, &colorBla2, &colorBla3, &colorBla4}; // Array of all colors fireworks can have

#define MIN_SPACE_BETWEEN_POSTIONS 2
#define NUMBER_POSITIONS 6
static uint8_t postions[] = {3, 5, 7, 9, 11, 13}; // Array of all valid x-cord positions for a firework to start

namespace details_firework {
    class Pixel {

    public:
        Pixel();

        float posX;
        float posY;

        float dirX;
        float dirY;

        Color color;
    };

    class Firework {

        Pixel *pixel[PIXEL_PER_FIREWORK];

        int8_t startPosX;
        int8_t startPosY;

        uint8_t lifeTime;
        bool arrived;
        bool exploded;


        void calcFireworkTrail(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);

        void calcFireworkExplosion(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);


    public:
        Firework();

        bool dead;

        void start(int8_t posX, int8_t posY, Color *color);

        void calcFrame(Color (*display)[MATRIX_HEIGHT][MATRIX_LENGTH]);
    };

}


class FireworkAnimation : public display_program {
    /*
    Color frame[MATRIX_HEIGHT][MATRIX_LENGTH];
    MatrixOutput *matrix;
     */


    uint8_t timeSinceLastFirework;
    uint8_t lastFireWorkPostion; // Index in position array
    uint8_t fireworkColor; // index in color array

    details_firework::Firework *firework[MAX_NUMBER_FIREWORKS];


    void calcFrame();

    void createNewFirework();

    void addNewFirework(int8_t explodePosX, int8_t explodePosY, Color *color);

    void blankFrame();


public:

    FireworkAnimation(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void refresh() override;
    void button1ISR(bool state) override;
    void button2ISR(bool state) override;
    void restart() override;


};


#endif //MUEK_ARGB_MATRIX_BOARD_FIREWORKANIMATION_H
