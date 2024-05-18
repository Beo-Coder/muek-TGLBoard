//
// Created by leo on 25.04.24.
//

#ifndef TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_H
#define TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_H

namespace details_dino_game{
    class Enemy;
    class Player;
}


#include <Arduino.h>
#include "display_program.h"
#include "dinogame_settings.h"




class DinoGame : public display_program {


    details_dino_game::Enemy *enemies[MAX_ENEMIES];
    uint8_t numberEnemies;
    details_dino_game::Player *player;

    bool dead = false;

    void animateFrame();

    void moveEntities();

    void createNewEnemy(uint8_t index);

    void checkScore();


public:
    uint32_t score;

    explicit DinoGame(MatrixOutput *ledMatrix, Color (*frame)[MATRIX_HEIGHT][MATRIX_LENGTH]);

    void button1ISR(bool data) override;

    void button2ISR(bool data) override;

    void refresh() override;

    void restart() override;


};


#endif //TGL_BOARD_FIREWORK_DINO_GAME_DINO_GAME_H
