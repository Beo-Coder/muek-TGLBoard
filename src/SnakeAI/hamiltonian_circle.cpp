//
// Created by leo on 01.05.24.
//

#include "hamiltonian_circle.h"

details_snake_ai::HamiltonianCircle::HamiltonianCircle() {
    pathIndex = 0;
    for(int i=0; i<MATRIX_SIZE;i++){
        path[i] = 0;
    }

}

void details_snake_ai::HamiltonianCircle::generatePath() {
    path[0] = 0;
    pathIndex = 1;
    int nattempts = 1 + 1.0 * 10.0 * MATRIX_SIZE * std::pow(std::log(2. + MATRIX_SIZE), 2);
    Serial.println(nattempts);
    while (pathIndex < MATRIX_SIZE) {
        for (int i = 0; i < nattempts; i++) {
            backbite();
        }
    }


}

void details_snake_ai::HamiltonianCircle::backbite() {
    uint16_t step;
    switch (randomInt(0,4)) {
        case 0:
            step = 1;
            break;
        case 1:
            step = -1;
            break;
        case 2:
            step = 1<<8;
            break;
        case 3:
            step = -(1<<8);
            break;
    }

    if (randomInt(0,2)) {
        backbiteLeft(step);
    } else {
        backbiteRight(step);
    }
}

void details_snake_ai::HamiltonianCircle::backbiteLeft(uint16_t step) {
    uint16_t neighbour = path[0]+step;
    if(legalPosition(neighbour)){
        bool alreadyInPath = false;
        int i;
        for(i=1; i<pathIndex;i++){
            if(neighbour == path[i]){
                alreadyInPath = true;
                break;
            }

        }
        if(alreadyInPath){
            reversePath(0, i-1);
        }else{
            reversePath(0,pathIndex-1);
            path[pathIndex] = neighbour;
            pathIndex++;
        }
    }


}

void details_snake_ai::HamiltonianCircle::backbiteRight(uint16_t step) {
    uint16_t neighbour = path[pathIndex-1]+step;
    if(legalPosition(neighbour)){
        bool alreadyInPath = false;
        int i;
        for(i=pathIndex-2; i>=0;i--){
            if(neighbour == path[i]){
                alreadyInPath = true;
                break;
            }

        }
        if(alreadyInPath){
            reversePath(i+1, pathIndex-1);
        }else{
            path[pathIndex] = neighbour;
            pathIndex++;
        }
    }

}

void details_snake_ai::HamiltonianCircle::reversePath(int i1, int i2) {

    int jlim = (i2-i1+1)/2;
    uint16_t temp;
    for (int j=0; j<jlim; j++)
    {
        temp = path[i1+j];
        path[i1+j] = path[i2-j];
        path[i2-j] = temp;
    }

}

void details_snake_ai::HamiltonianCircle::generate() {
    generateCircle();
    for(int i=0; i<MATRIX_SIZE;i++){
        Serial.print(path[i]);
        Serial.print(" ");
    }
    Serial.print("\n\r");

}

bool details_snake_ai::HamiltonianCircle::legalPosition(uint16_t node) {

    //if((index/LENGTH == pathIndex/LENGTH && index%LENGTH >= (pathIndex-1)%LENGTH && index%LENGTH <= (pathIndex+1)%LENGTH)) return false;
    //if((index%LENGTH == pathIndex%LENGTH && index/LENGTH >= (pathIndex-1)/LENGTH && index/LENGTH <= (pathIndex+1)/LENGTH)) return false;

    // if(pathIndex/MATRIX_LENGTH != index/(MATRIX_LENGTH)) return false;
    // if(pathIndex/MATRIX_HEIGHT != index/(MATRIX_HEIGHT)) return false;


    uint16_t x=node&0xFF;
    uint16_t y=(node>>8)&0xFF;

    if(x<0) return false;
    if(x>=MATRIX_LENGTH) return false;
    if(y<0) return false;
    if(y>=MATRIX_HEIGHT) return false;


/*
    if(index < 0) return false;
    if(index >= MATRIX_SIZE) return false;

    if(index/LENGTH + 1 == path[pathIndex-1]/LENGTH && index%LENGTH != path[pathIndex-1]%LENGTH) return false;
    if(index/LENGTH - 1 == path[pathIndex-1]/LENGTH && index%LENGTH != path[pathIndex-1]%LENGTH) return false;
*/
    //if(index/(MATRIX_LENGTH) > (MATRIX_HEIGHT)) return false;
    //if(index/(MATRIX_LENGTH) < 0) return false;

    //if((pathIndex-1)/LENGTH >= index/(LENGTH) && (pathIndex+1)/LENGTH <= index/(LENGTH) && pathIndex%LENGTH != index%(LENGTH)) return false;
    //if((pathIndex-1)%LENGTH >= index%(LENGTH) && (pathIndex+1)%LENGTH <= index%(LENGTH) && pathIndex/LENGTH != index/(LENGTH)) return false;
    return true;
}

void details_snake_ai::HamiltonianCircle::generateCircle() {
    generatePath();
    int min_dist = 1 + (pathIndex % 2);
    while (abs(path[pathIndex - 1] - path[0]) != min_dist) {
        // while (path[pathIndex - 1] - path[0] != min_dist) {
        backbite();
    }


}