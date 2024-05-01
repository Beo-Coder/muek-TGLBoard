//
// Created by leo on 01.05.24.
//

#ifndef MUEK_ARGB_MATRIX_BOARD_HAILTIONIAN_CIRCLE_H
#define MUEK_ARGB_MATRIX_BOARD_HAILTIONIAN_CIRCLE_H

#include "Arduino.h"
#include "PIOMatrixOutput/pio_matrix_output.h"
#include "BeoCommon.h"
#include "snake_ai_settings.h"


namespace details_snake_ai {
    class HamiltonianCircle{


        int pathIndex;

        void generateCircle();

        void generatePath();
        void backbite();

        void backbiteLeft(uint16_t step);
        void backbiteRight(uint16_t step);
        void reversePath(int i1, int i2);

        bool legalPosition(uint16_t node);


    public:
        uint16_t path[MATRIX_SIZE];
        HamiltonianCircle();
        void generate();

    };
}


#endif //MUEK_ARGB_MATRIX_BOARD_HAILTIONIAN_CIRCLE_H
