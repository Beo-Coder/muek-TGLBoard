//
// Created by leo on 27.04.24.
//

#include "BeoCommon.h"



int randomInt(int min, int max){
    int range = (max-min);
    uint32_t randomNumber;
    for(int i=0; i<4*8;i++){
        randomNumber = (randomNumber << 1) | rosc_hw->randombit;
    }

    return int(randomNumber % range) + min;
}

/*
uint32_t abs(int32_t value){
    if(value < 0){
        return value*(-1);
    }
    return value;
}
 */


