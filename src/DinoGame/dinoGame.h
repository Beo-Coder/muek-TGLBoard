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
class FlashController;


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif



#include "display_program.h"
#include "dinogame_settings.h"
#include <string>




class DinoGame : public DisplayProgram {

    FlashController *flashController;
    TextController *textController;
    std::string stringBuffer;

    details_dino_game::Enemy *enemies[details_dino_game::MAX_ENEMIES];
    uint8_t numberEnemies;
    details_dino_game::Player *player;

    bool dead;
    uint8_t showScore;

    void animateFrame();

    void moveEntities();

    void createNewEnemy(uint8_t index);

    void checkScore();

    uint32_t getHighScore();
    void storeNewHighScore();
    void checkHighScore();


public:
    uint32_t score;

    explicit DinoGame(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH], TextController *staticController, FlashController *flashController);

    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;


};


#endif //TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_H
