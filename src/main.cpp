#include <Arduino.h>
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/irq.h"

#include "letters.h"
#include "pioMatrixOutput.h"


PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);

uint32_t display[8][16];


void setup() {
    color color1{};
    color1.red = 50;
    color1.green = 0;
    color1.blue = 0;

    color color2{};
    color2.red = 0;
    color2.green = 0;
    color2.blue = 0;

    for(int i=0;i<5;i++){
        for(int j=0; j<8;j++){
            if((lA[j] >> i) & 0x01){
                display[j][i] = *(uint32_t *) &color1;
            }else{
                display[j][i] = *(uint32_t *) &color2;
            }

        }
    }

    for (int i = 0; i < 128; i++) {

            ledMatrix.matrix[i/64][i % 64] = display[i/16][i%16];

    }
    ledMatrix.sendData();
    /*


    for (int i = 0; i < 128; i++) {
        color1.red = 255;
        color1.green = 0;
        color1.blue = 0;


        ledMatrix.matrix[i / 64][i % 64] = *(uint32_t *) &color1;
    }
    ledMatrix.sendData();


    delay(1000);
    for (int i = 0; i < 128; i++) {
        color1.red = 100;
        color1.green = 0;
        color1.blue = 100;


        ledMatrix.matrix[i / 64][i % 64] = *(uint32_t *) &color1;
    }
    ledMatrix.sendData();
     */


    //Serial1.begin(115200);

    /*
    // Get program offset
    uint offset = pio_add_program(pio, &argb_program);

    //init pio state machine
    argb_program_init(pio, 0, offset, 10, 11, 32);




    dma_channel_config dmac = dma_channel_get_default_config(0);


    channel_config_set_transfer_data_size(&dmac, DMA_SIZE_32);
    channel_config_set_read_increment(&dmac, true);
    channel_config_set_write_increment(&dmac, false);

    //channel_config_set_chain_to(&dmac, 1);
    //channel_config_set_irq_quiet(&dmac, true);
    //channel_config_set_ring(&dmac, false, 12);


    channel_config_set_dreq(&dmac, pio_get_dreq(pio, 0, true));


    dma_channel_configure(0,
                          &dmac,
                          &pio->txf[0], // Destination pointer
                          send, // Source pointer
                          128*3/4, // Number of transfers
                          true // Start immediately
    );


    //dma_channel_set_irq0_enabled(0, true);
    //irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    //irq_set_enabled(DMA_IRQ_0, true);


    pio_sm_set_enabled(pio, 0, true);

*/

    delay(1000);
    pio_sm_set_enabled(pio, 0, false);
}


void loop() {
    tight_loop_contents();
}
