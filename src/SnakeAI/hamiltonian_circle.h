//
// © 2024 Leonhard Baschang
//

#ifndef TGL_BOARD_SNAKE_AI_HAMILTONIAN_CIRCLE_H
#define TGL_BOARD_SNAKE_AI_HAMILTONIAN_CIRCLE_H


#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "PIOMatrixOutput/pio_matrix_settings.h"
#include "snake_ai_settings.h"

#define PRIM_LENGTH (MATRIX_LENGTH/2)
#define PRIM_HEIGHT (MATRIX_HEIGHT/2)
#define PRIM_SIZE (PRIM_LENGTH*PRIM_HEIGHT)

namespace details_snake_ai {
    class HamiltonianCircle{

        const Direction directionArray[4] = {Right, Left, Up, Down};

        // For hamiltonian cycle
        uint16_t nodesInPath;
        bool nodesSelected[MATRIX_SIZE];

        // For prims algorithm
        uint16_t edges[PRIM_SIZE];
        uint16_t numberEdges;
        bool edgeSelected[PRIM_SIZE];


        static uint16_t getXFromIndexPrim(uint16_t index);
        static uint16_t getYFromIndexPrim(uint16_t index);

        static bool isAdjacentPrim(uint16_t index1, uint16_t index2);

        void primsAlgorithm();


        static bool isLegalPosition(uint16_t pos);

        static uint16_t postionToPrimIndex(uint16_t pos);

        static uint16_t positionToIndex(uint16_t pos);

        static bool onSameCell(uint16_t pos, int16_t dir);

        bool hasEdgeInDirection(uint16_t pos, int16_t dir);

        bool hasNoEdge(uint16_t pos, int32_t dir);

        uint16_t getNextNode(uint16_t pos);

        void createHamiltonianCycle();



    public:
        uint16_t path[MATRIX_SIZE];
        void generate();

    };
}


#endif //TGL_BOARD_SNAKE_AI_HAMILTONIAN_CIRCLE_H
