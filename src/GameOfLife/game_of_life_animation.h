//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_GAME_OF_LIFE_GAME_OF_LIFE_ANIMATION_H
#define TGL_BOARD_GAME_OF_LIFE_GAME_OF_LIFE_ANIMATION_H

#include "display_program.h"


namespace details_game_of_life{

    inline const uint32_t REFRESH_SPEED = 150;

    inline const uint16_t waitTicksBeforeReset = 3;

    inline const Color *cellColors[] = {&colorGreen, &colorRed, &colorPurple, &colorCyan, &colorYellow};
    inline const uint8_t numberCellColors = 5;






    inline const uint8_t startPattern[3][3] ={{0,1,0},
                                              {0,0,1},
                                              {1,1,1}};
    inline const uint8_t startPatternXPos = MATRIX_LENGTH/2 - 2;
    inline const uint8_t startPatternYPos = MATRIX_HEIGHT/2 - 2;

}




class GameOfLife : public DisplayProgram {


    uint8_t generations[3][MATRIX_SIZE];
    uint8_t generationIndex;

    uint16_t gameTicks;
    uint16_t deadGameTicks;

    const Color *gameColor;
    uint8_t lastColorIndex;

    uint8_t getNeighbours(uint8_t xPos, uint8_t yPos);

    bool isAlive(uint8_t xPos, uint8_t yPos);



    static uint16_t postionToIndex(uint8_t xPos, uint8_t yPos);

    void fillWithRandomPattern(uint8_t index);

    void clearGeneration(uint8_t index);

    void addStartPattern(uint8_t index);

    bool isDead();

    void calcNextGen();

    void loadIntoFrame(uint8_t loadGenerationIndex);


public:

    GameOfLife(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void refresh() override;
    void button1ISR(bool state) override;
    void button2ISR(bool state) override;
    void restart() override;

};


#endif //TGL_BOARD_GAME_OF_LIFE_GAME_OF_LIFE_ANIMATION_H
