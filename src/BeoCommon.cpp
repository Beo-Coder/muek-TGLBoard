//
// Created by leo on 27.04.24.
//

#include "BeoCommon.h"



int randomInt(int min, int max){
    int range = (max-min);
    return rand() % range + min;
}


