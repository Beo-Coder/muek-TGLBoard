//
// Created by leo on 01.05.24.
//



#ifndef TGL_BOARD_FIREWORK_FIREWORK_SETTINGS_H
#define TGL_BOARD_FIREWORK_FIREWORK_SETTINGS_H

#include "PIOMatrixOutput/color.h"

#define SIMULATION_SPEED 220

#define PIXEL_PER_FIREWORK (4*3) // Should be a multiple of 4 (for each direction)
#define PIXEL_PER_FIREWORK_TRAIL 2
#define TIME_DELAY_ARRIVAL_EXPLOSION 2

#define FIREWORK_LIFE_TIME 10
#define TIME_BETWEEN_FIREWORKS 7

#define MAX_NUMBER_FIREWORKS 4

#define FIREWORK_EXPLODE_Y_MIN 4
#define FIREWORK_EXPLODE_Y_MAX 7

#define FIREWORK_EXPLOSION_BRIGHTNESS_MAX 55 // actually 100 times less (more than NORMAL_BRIGHTNESS)
#define FIREWORK_EXPLOSION_BRIGHTNESS_MIN 45 // actually 100 times less (more than NORMAL_BRIGHTNESS)
#define TIME_BETWEEN_EXPLOSION_AFTER_EXPLOSION_BRIGHTNESS 1
#define FIREWORK_AFTER_EXPLOSION_BRIGHTNESS (NORMAL_BRIGHTNESS + 6)
#define FIREWORK_AFTER_EXPLOSION_BRIGHTNESS_SINKRATE_MAX 50 // actually 100 times less
#define FIREWORK_AFTER_EXPLOSION_BRIGHTNESS_SINKRATE_MIN 35 // actually 100 times less


// Only Change if you know what you are doing
#define FIREWORK_SPEED_VALUE_X 7 // Value does not represent real pixel or something
#define FIREWORK_SPEED_VALUE_Y 7 // Value does not represent real pixel or something

#define FIREWORK_SPEED_VALUE_X2 15 // Value does not represent real pixel or something
#define FIREWORK_SPEED_VALUE_Y2 15 // Value does not represent real pixel or something

#define FIREWORK_DECELERATION_VALUE_X 10 // Value does not represent real pixel or something
#define FIREWORK_DECELERATION_VALUE_Y 10 // Value does not represent real pixel or something

#define FIREWORK_SINK_RATE (0.01) // Value dos not represent real pixel or something
// End of change only if you know


static Color *trailColor = &colorWhite;

#define NUMBER_FIREWORK_COLORS 6
static Color *randomColor[NUMBER_FIREWORK_COLORS] = {&colorRed, &colorBlue, &colorGreen, &colorYellow, &colorCyan,&colorPurple}; // Array of all colors fireworks can have



#define MIN_SPACE_BETWEEN_POSTIONS 2
#define NUMBER_POSITIONS 7
static uint8_t postions[NUMBER_POSITIONS] = {2, 3, 5, 7, 9, 11, 13}; // Array of all valid x-cord positions for a firework to start



#endif //TGL_BOARD_FIREWORK_FIREWORK_SETTINGS_H
