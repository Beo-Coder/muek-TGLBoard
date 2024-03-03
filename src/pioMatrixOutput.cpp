//
// Created by Leo Baschang on 02.03.24.
//

#include "pioMatrixOutput.h"


MatrixOutput::MatrixOutput(PIO pio, uint8_t sm, uint8_t dmaChannel, uint8_t pin_1, uint8_t pin_2) {
    this->pio = pio;
    this->sm = sm;
    this->dmaChannel = dmaChannel;
    uint offset = pio_add_program(pio, &argb_program);

    //init pio state machine
    argb_program_init(pio, sm, offset, pin_1, pin_2, 32);


    dmac = dma_channel_get_default_config(sm);


    channel_config_set_transfer_data_size(&dmac, DMA_SIZE_32);
    channel_config_set_read_increment(&dmac, true);
    channel_config_set_write_increment(&dmac, false);


    channel_config_set_dreq(&dmac, pio_get_dreq(pio, sm, true));

    dma_channel_configure(sm,
                          &dmac,
                          &pio->txf[0], // Destination pointer
                          sendMatrix, // Source pointer
                          MATRIX_SIZE * 3 / 4, // Number of transfers
                          false // Start immediately
    );


    pio_sm_set_enabled(pio, sm, false);

}

void MatrixOutput::sendData() {
    int bitsShifted = 0;
    for (int i = 0; i < MATRIX_SUBMATRIX_SIZE; i++) {
        for (int j = 0; j < 24; j++) {
            for (int k = 0; k < MATRIX_SUBMATRIX_COUNT; k++) {
                sendMatrix[bitsShifted / 32] =
                        (sendMatrix[bitsShifted / 32] << 1) |
                        ((matrix[MATRIX_SUBMATRIX_COUNT - 1 - k][i] >> (23 - j) & 0x01));
                bitsShifted++;
            }
        }
    }

    dma_channel_set_read_addr(dmaChannel, sendMatrix, true);

    pio_sm_set_enabled(pio, sm, true);
}
