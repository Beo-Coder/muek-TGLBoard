//
// Created by leo on 01.05.24.
//



#ifndef TGL_BOARD_FIREWORK_FIREWORK_SETTINGS_H
#define TGL_BOARD_FIREWORK_FIREWORK_SETTINGS_H

#include "PIOMatrixOutput/color.h"

namespace details_firework{
    inline const uint32_t SIMULATION_SPEED = 220;

    inline const uint8_t PIXEL_PER_FIREWORK = (4*3); // Should be a multiple of 4 (for each direction)
    inline const uint8_t PIXEL_PER_FIREWORK_TRAIL = 2;
    inline const uint8_t TIME_DELAY_ARRIVAL_EXPLOSION = 2;

    inline const uint8_t FIREWORK_LIFE_TIME = 10;
    inline const uint8_t TIME_BETWEEN_FIREWORKS = 7;

    inline const uint8_t MAX_NUMBER_FIREWORKS = 4;

    inline const uint8_t FIREWORK_EXPLODE_Y_MIN = 4;
    inline const uint8_t FIREWORK_EXPLODE_Y_MAX = 7;

    inline const uint8_t FIREWORK_EXPLOSION_BRIGHTNESS_MAX = 55; // more than NORMAL_BRIGHTNESS
    inline const uint8_t FIREWORK_EXPLOSION_BRIGHTNESS_MIN = 45; // more than NORMAL_BRIGHTNESS
    inline const uint8_t TIME_BETWEEN_EXPLOSION_AFTER_EXPLOSION_BRIGHTNESS = 1;
    inline const uint8_t FIREWORK_AFTER_EXPLOSION_BRIGHTNESS = (NORMAL_BRIGHTNESS + 6);
    inline const uint8_t FIREWORK_AFTER_EXPLOSION_BRIGHTNESS_SINKRATE_MAX = 50; // actually 100 times less
    inline const uint8_t FIREWORK_AFTER_EXPLOSION_BRIGHTNESS_SINKRATE_MIN = 35; // actually 100 times less


// Only Change if you know what you are doing
    inline const uint8_t FIREWORK_SPEED_VALUE_X = 7; // Value does not represent real pixel or something
    inline const uint8_t FIREWORK_SPEED_VALUE_Y = 7; // Value does not represent real pixel or something

    inline const uint8_t FIREWORK_SPEED_VALUE_X2 = 15; // Value does not represent real pixel or something
    inline const uint8_t FIREWORK_SPEED_VALUE_Y2 = 15; // Value does not represent real pixel or something

    inline const uint8_t FIREWORK_DECELERATION_VALUE_X = 10; // Value does not represent real pixel or something
    inline const uint8_t FIREWORK_DECELERATION_VALUE_Y = 10; // Value does not represent real pixel or something

    inline const float FIREWORK_SINK_RATE = 0.01; // Value dos not represent real pixel or something
// End of change only if you know


    inline Color *trailColor = &colorWhite;

    inline const uint8_t NUMBER_FIREWORK_COLORS = 6;
    inline Color *randomColor[NUMBER_FIREWORK_COLORS] = {&colorRed, &colorBlue, &colorGreen, &colorYellow, &colorCyan,&colorPurple}; // Array of all colors fireworks can have



    inline const uint8_t MIN_SPACE_BETWEEN_POSTIONS = 2;
    inline const uint8_t NUMBER_POSITIONS = 7;
    inline uint8_t postions[NUMBER_POSITIONS] = {2, 3, 5, 7, 9, 11, 13}; // Array of all valid x-cord positions for a firework to start

}



#endif //TGL_BOARD_FIREWORK_FIREWORK_SETTINGS_H
