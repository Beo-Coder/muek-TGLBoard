//
// Created by leo on 27.04.24.
//

#include "beo_common.h"
#include <hardware/structs/rosc.h>
#include <hardware/timer.h>

int beo::randomInt(int min, int max){
    int range = (max-min);
    uint32_t randomNumber;
    for(int i=0; i<4*8;i++){
        randomNumber = (randomNumber << 1) | rosc_hw->randombit;
    }

    return int(randomNumber % range) + min;
}

unsigned long beo::millis() {
    return (timer_hw->timerawl) / 1000;

}


