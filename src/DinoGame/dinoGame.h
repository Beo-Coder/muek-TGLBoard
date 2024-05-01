//
// Created by leo on 25.04.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_DINOGAME_H
#define MUEK_ARGB_MATRIX_BOARD_DINOGAME_H

#include "Arduino.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "color.h"
#include "display_program.h"
#include "BeoCommon.h"

#include "dinogame_settings.h"
#include "entity.h"
#include "enemy.h"
#include "player.h"



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


#endif //MUEK_ARGB_MATRIX_BOARD_DINOGAME_H
