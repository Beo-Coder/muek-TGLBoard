//
// Created by leo on 01.05.24.
//

#include "Arduino.h"
#include "color.h"

#ifndef MUEK_ARGB_MATRIX_BOARD_FIREWORK_SETTINGS_H
#define MUEK_ARGB_MATRIX_BOARD_FIREWORK_SETTINGS_H


#define SIMULATION_SPEED 220

#define PIXEL_PER_FIREWORK (4*3) // Should be a multiple of 4 (for each direction)
#define PIXEL_PER_FIREWORK_TRAIL 2
#define TIME_DELAY_ARRIVAL_EXPLOSION 2

#define FIREWORK_LIFE_TIME 9
#define TIME_BETWEEN_FIREWORKS 7

#define MAX_NUMBER_FIREWORKS 5

#define FIREWORK_EXPLODE_Y_MIN 4
#define FIREWORK_EXPLODE_Y_MAX 7

#define FIREWORK_EXPLOSION_BRIGHTNESS (NORMAL_BRIGHTNESS + (randomInt(40,50)))
#define FIREWORK_AFTER_EXPLOSION_BRIGHTNESS (NORMAL_BRIGHTNESS + 6)
#define FIREWORK_AFTER_EXPLOSION_BRIGHTNESS_SINKRATE (1.5)


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
#define NUMBER_POSITIONS 6
static uint8_t postions[NUMBER_POSITIONS] = {3, 5, 7, 9, 11, 13}; // Array of all valid x-cord positions for a firework to start



#endif //MUEK_ARGB_MATRIX_BOARD_FIREWORK_SETTINGS_H
