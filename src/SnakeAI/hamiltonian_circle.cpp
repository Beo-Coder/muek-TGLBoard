//
// Created by leo on 01.05.24.
//

#include "hamiltonian_circle.h"
#include "beo_common.h"


uint16_t details_snake_ai::HamiltonianCircle::getXFromIndexPrim(uint16_t index){
    return index % PRIM_LENGTH;
}

uint16_t details_snake_ai::HamiltonianCircle::getYFromIndexPrim(uint16_t index){
    return index / PRIM_LENGTH;
}

bool details_snake_ai::HamiltonianCircle::isAdjacentPrim(uint16_t index1, uint16_t index2){
    uint16_t deltaX = absolut(getXFromIndexPrim(index1) - getXFromIndexPrim(index2));
    uint16_t deltaY = absolut(getYFromIndexPrim(index1) - getYFromIndexPrim(index2));
    return (deltaX == 1 && deltaY == 0) || (deltaX == 0 && deltaY == 1);
}




void details_snake_ai::HamiltonianCircle::primsAlgorithm(){

    for(uint16_t i=0; i < PRIM_SIZE; i++){
        edgeSelected[i] = false;
    }

    edges[0] = 0;
    numberEdges = 1;
    edgeSelected[0] = true;


    while(numberEdges < PRIM_SIZE){

        uint16_t minimumNodeI = MATRIX_SIZE;
        uint16_t minimumNodeJ = MATRIX_SIZE;
        uint16_t minimumNodeValue = UINT16_MAX;

        for(uint16_t i=0; i < PRIM_SIZE; i++){
            if(edgeSelected[i]){

                for(uint16_t j=0; j < PRIM_SIZE; j++){
                    if(!edgeSelected[j] && isAdjacentPrim(i, j)){
                        uint16_t randomValue = beo::randomInt(0, UINT16_MAX);
                        if(minimumNodeValue > randomValue){
                            minimumNodeValue = randomValue;
                            minimumNodeI = i;
                            minimumNodeJ = j;
                        }

                    }
                }

            }


        }

        edges[minimumNodeJ] = minimumNodeI;
        numberEdges++;
        edgeSelected[minimumNodeJ] = true;

    }


}



bool details_snake_ai::HamiltonianCircle::isLegalPosition(uint16_t pos){
    uint8_t x = pos & 0xFF;
    uint8_t y = (pos >> 8) & 0xFF;

    if(x < 0){ return false;}
    if(x >= MATRIX_LENGTH){ return false;}

    if(y < 0){ return false;}
    if(y >= MATRIX_HEIGHT){ return false;}

    return true;
}

uint16_t details_snake_ai::HamiltonianCircle::postionToPrimIndex(uint16_t pos){

    if(!isLegalPosition(pos)){
        return PRIM_SIZE;
    }

    uint8_t x = pos &0xFF;
    uint8_t y = (pos >>8) &0xFF;

    x = x/2;
    y = y/2;
    return x+(y * PRIM_LENGTH);
}

uint16_t details_snake_ai::HamiltonianCircle::positionToIndex(uint16_t pos){
    uint8_t x = pos & 0xFF;
    uint8_t y = (pos >> 8) & 0xFF;

    return x + (y*MATRIX_LENGTH);
}


// Prim index = cell index
bool details_snake_ai::HamiltonianCircle::onSameCell(uint16_t pos, int16_t dir){
    uint16_t primIndex = postionToPrimIndex(pos);

    uint16_t neighbourPrimIndex = postionToPrimIndex(pos + dir);
    return primIndex == neighbourPrimIndex;

}


bool details_snake_ai::HamiltonianCircle::hasEdgeInDirection(uint16_t pos, int16_t dir){
    uint16_t primIndex = postionToPrimIndex(pos);
    uint16_t neighbourPrimIndex = postionToPrimIndex(pos + dir);
    if(onSameCell(pos, dir)){
        return false;
    }

    if(edges[primIndex] == neighbourPrimIndex){
        return true;
    }
    if(edges[neighbourPrimIndex] == primIndex){
        return true;
    }

    return false;

}





bool details_snake_ai::HamiltonianCircle::hasNoEdge(uint16_t pos, int32_t dir){
    if(absolut(dir) == 1){
        if(hasEdgeInDirection(pos, (1 << 8)) || hasEdgeInDirection(pos, -(1 << 8))){
            return false;
        }
    }
    if(absolut(dir) == (1 << 8)){
        if(hasEdgeInDirection(pos, 1) || hasEdgeInDirection(pos, -1)){
            return false;
        }
    }
    return true;
}






uint16_t details_snake_ai::HamiltonianCircle::getNextNode(uint16_t pos){

    for(int i=0; i<4; i++){
        int16_t dir = directionArray[i];

        // Position is inside of Matrix
        if(isLegalPosition(pos + dir)){
            // If it has an edge, follow it
            if (hasEdgeInDirection(pos, dir) && !nodesSelected[positionToIndex(pos + dir)]) {
                return pos+dir;
            }
        }
    }

    for(int i=0; i<4; i++){
        int16_t dir = directionArray[i];

        // Position is inside of Matrix
        if(isLegalPosition(pos + dir)){
            // If it is on the same cell, go to the only possible location
            if(onSameCell(pos, dir) && !nodesSelected[positionToIndex(pos + dir)] && hasNoEdge(pos, dir)){
                return pos+dir;
            }
        }
    }

    return path[0];


}








void details_snake_ai::HamiltonianCircle::createHamiltonianCycle(){

    for(uint16_t i=0; i<MATRIX_SIZE; i++){
        nodesSelected[i] = false;
    }

    nodesSelected[0] = true;
    path[0] = 0;
    nodesInPath = 1;


    while (nodesInPath < MATRIX_SIZE){
        uint16_t nextNode = getNextNode(path[nodesInPath-1]);
        path[nodesInPath] = nextNode;
        nodesSelected[positionToIndex(nextNode)] = true;
        nodesInPath++;
    }

}


void details_snake_ai::HamiltonianCircle::generate() {
    primsAlgorithm();
    createHamiltonianCycle();

    // Invert the y coordinate, because I messed up (maybe not necessary)
    for(int i=0; i<MATRIX_SIZE;i++){
        path[i] =  (( (MATRIX_HEIGHT - 1  - ((path[i] >> 8) & 0xFF))) << 8) | (path[i] & 0xFF);
    }
}
