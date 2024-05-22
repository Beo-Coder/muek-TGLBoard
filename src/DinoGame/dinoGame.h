//
// Created by leo on 25.04.24.
//

#ifndef TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_H
#define TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_H

namespace details_dino_game{
    class Enemy;
    class Player;
}
class TextController;


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif



#include "display_program.h"
#include "dinogame_settings.h"
#include <string>




class DinoGame : public DisplayProgram {

    TextController *textController;
    std::string stringBuffer;

    details_dino_game::Enemy *enemies[MAX_ENEMIES];
    uint8_t numberEnemies;
    details_dino_game::Player *player;

    bool dead;
    bool showScore;

    void animateFrame();

    void moveEntities();

    void createNewEnemy(uint8_t index);

    void checkScore();


public:
    uint32_t score;

    explicit DinoGame(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], TextController *staticController);

    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;


};


#endif //TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_H
