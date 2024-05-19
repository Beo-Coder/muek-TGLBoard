//
// Created by leo on 18.05.24.
//

#ifndef TGL_BOARD_PIO_MATRIX_OUTPUT_PIO_MATRIX_SETTINGS_H
#define TGL_BOARD_PIO_MATRIX_OUTPUT_PIO_MATRIX_SETTINGS_H


#define MATRIX_LENGTH 16
#define MATRIX_HEIGHT 8


#define MATRIX_SUBMATRIX_COUNT 2


#define MATRIX_SIZE (MATRIX_LENGTH*MATRIX_HEIGHT)
#define MATRIX_SUBMATRIX_SIZE (MATRIX_SIZE/MATRIX_SUBMATRIX_COUNT)


#define MAX_FRAMES_IN_BUFFER 10
#define MAX_SUBFRAMES 8

#define TIMER_INDEX 1

#define dataSendTime (1920 + 50 + 6) // (time_to_output_data + time_to_latch_data + some_buffer_time) (in µs)
#define subframePauseIntervall (0) // Time to add after dataSendTime in µs. Only in steps of 10. +/- 5µs

#endif //TGL_BOARD_PIO_MATRIX_OUTPUT_PIO_MATRIX_SETTINGS_H
