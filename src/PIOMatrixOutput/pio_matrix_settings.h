//
// Created by leo on 18.05.24.
//

#ifndef MUEK_TGL_BOARD2_PIO_MATRIX_SETTINGS_H
#define MUEK_TGL_BOARD2_PIO_MATRIX_SETTINGS_H


#define MATRIX_LENGTH 16
#define MATRIX_HEIGHT 8


#define MATRIX_SUBMATRIX_COUNT 2


#define MATRIX_SIZE (MATRIX_LENGTH*MATRIX_HEIGHT)
#define MATRIX_SUBMATRIX_SIZE (MATRIX_SIZE/MATRIX_SUBMATRIX_COUNT)


#define MAX_FRAMES_IN_BUFFER 10
#define MAX_SUBFRAMES 8

#define TIMER_INDEX 1

#define dataSendTime 1950 // in µs
#define subframePauseIntervall 350 // in µs (must be at least 150 (probably more))

#endif //MUEK_TGL_BOARD2_PIO_MATRIX_SETTINGS_H
