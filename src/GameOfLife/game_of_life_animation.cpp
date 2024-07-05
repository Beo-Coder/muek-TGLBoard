//
// © 2024 Leonhard Baschang
//

#include "game_of_life_animation.h"
#include "beo_common.h"


GameOfLife::GameOfLife(MatrixOutput *ledMatrix, Color (*frame)[8][16]) : DisplayProgram(ledMatrix, frame) {
    refreshSpeed = details_game_of_life::REFRESH_SPEED;
    gameTicks = 0;
    deadGameTicks = 0;
    for(int i=0; i<3; i++){
        clearGeneration(i);
    }
    gameColor = &colorGreen;
    lastColorIndex = details_game_of_life::numberCellColors;


    generationIndex = 0;

}



uint16_t GameOfLife::postionToIndex(uint8_t xPos, uint8_t yPos) {
    return xPos + yPos*MATRIX_LENGTH;
}



uint8_t GameOfLife::getNeighbours(uint8_t xPos, uint8_t yPos) {
    uint8_t count = 0;

    for(int i=xPos-1; i<=xPos+1; i++){
        for(int j=yPos-1; j<=yPos+1; j++){



            // Wrap at borders
            uint8_t localX = (i+MATRIX_LENGTH) % MATRIX_LENGTH;
            uint8_t localY = (j+MATRIX_HEIGHT) % MATRIX_HEIGHT;


            if(localX==xPos && localY==yPos){
                continue;
            }

            uint16_t index = postionToIndex(localX,localY);
            if(generations[generationIndex][index] != 0){
                count++;
            }


        }
    }

    return count;
}

bool GameOfLife::isAlive(uint8_t xPos, uint8_t yPos) {
    uint16_t index = postionToIndex(xPos, yPos);

    return generations[generationIndex][index] != 0;
}


void GameOfLife::fillWithRandomPattern(uint8_t index) {

    for(int i=0; i<MATRIX_LENGTH; i++){
        for(int j=0; j<MATRIX_HEIGHT; j++){

            generations[index][postionToIndex(i, j)] = beo::randomInt(0,2);
        }


    }

}


void GameOfLife::addStartPattern(uint8_t index) {

    for(int i=details_game_of_life::startPatternXPos; i<details_game_of_life::startPatternXPos+3; i++){
        for(int j=details_game_of_life::startPatternYPos; j<details_game_of_life::startPatternYPos+3; j++){

            generations[index][postionToIndex(i,j)] = details_game_of_life::startPattern[j-details_game_of_life::startPatternYPos][i-details_game_of_life::startPatternXPos];
        }


    }

}


void GameOfLife::clearGeneration(uint8_t index) {
    for(int j=0; j<MATRIX_SIZE; j++){
        generations[index][j] = 0;
    }

}



void GameOfLife::calcNextGen() {

    uint8_t nextGenerationIndex = (generationIndex + 1) % 3;
    clearGeneration(nextGenerationIndex);

    for(int i=0; i<MATRIX_LENGTH; i++){
        for(int j=0; j<MATRIX_HEIGHT; j++){
            uint8_t liveNeighbours = getNeighbours(i,j);
            uint16_t cellArrayIndex = postionToIndex(i,j);

            switch (liveNeighbours){

                case 0:
                case 1:
                    generations[nextGenerationIndex][cellArrayIndex] = 0;
                    break;

                case 2:
                    if(isAlive(i,j)){
                        generations[nextGenerationIndex][cellArrayIndex] = 1;
                    }
                    break;
                case 3:
                    generations[nextGenerationIndex][cellArrayIndex] = 1;
                    break;
                default:
                    generations[nextGenerationIndex][cellArrayIndex] = 0;
                    break;

            }

        }
    }

    generationIndex = nextGenerationIndex;



}

void GameOfLife::loadIntoFrame(uint8_t loadGenerationIndex) {
    for(int i=0; i<MATRIX_LENGTH; i++){
        for(int j=0; j<MATRIX_HEIGHT; j++){
            if(generations[loadGenerationIndex][postionToIndex(i,j)] != 0){
                (*frame)[j][i] = *gameColor;
            }else{
                (*frame)[j][i] = colorBlank;
            }
        }
    }

}





void GameOfLife::refresh() {
    // Serial.println(gameTicks);

    if(!isDead()){
        calcNextGen();
        loadIntoFrame(generationIndex);
        matrix->setDisplayData(frame);
        matrix->sendData();
    }else{
        if(deadGameTicks == 0){
            deadGameTicks = gameTicks;
        }
        if(gameTicks >= deadGameTicks + details_game_of_life::waitTicksBeforeReset){
            restart();
        }
    }
    gameTicks++;



}

void GameOfLife::button1ISR(bool state) {

}

void GameOfLife::button2ISR(bool state) {

}

void GameOfLife::restart() {
    gameTicks = 0;
    deadGameTicks = 0;
    for(int i=0; i<3; i++){
        clearGeneration(i);
    }
    uint8_t colorIndex = beo::randomInt(0, details_game_of_life::numberCellColors);
    if(colorIndex == lastColorIndex){
        colorIndex = (colorIndex + 1)%details_game_of_life::numberCellColors;
    }
    gameColor = details_game_of_life::cellColors[colorIndex];
    lastColorIndex = colorIndex;


    generationIndex = 0;
    fillWithRandomPattern(generationIndex);
    // addStartPattern(0);

    loadIntoFrame(generationIndex);
    matrix->setDisplayData(frame);
    matrix->sendData();



}

bool GameOfLife::isDead() {
    for(int i=0; i<MATRIX_SIZE; i++){
        if(generations[0][i] != generations[2][i]){
            return false;
        }
    }

    return true;
}





