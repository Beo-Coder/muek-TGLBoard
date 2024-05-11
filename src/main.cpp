#include <stdio.h>

#include "pico/stdlib.h"
#include <string>

#include "hardware/pio.h"
#include "hardware/irq.h"

#include "PIOMatrixOutput/pio_matrix_output.h"
#include "PIOMatrixOutput/color.h"

#include "ScrollText/scroll_text.h"
#include "DinoGame/dinoGame.h"
#include "Firework/firework_animation.h"
#include "SnakeAI/snake_ai_animation.h"


#define BUTTON1 18
#define BUTTON2 19

Color color1(5,0,0);
Color color2(0,0,0);


Color frame[8][16];

uint32_t lastMillis = 0;


std::string text = "Now also in C%/Cpp SDK   ";

PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);


ScrollText scrollTextController(&ledMatrix, &frame);
DinoGame game(&ledMatrix, &frame);
FireworkAnimation fireworks(&ledMatrix, &frame);
SnakeAI snake(&ledMatrix, &frame);


display_program *programs[2];



void button_isr(uint gpio, uint32_t events) {
    uint8_t state = events>>3; // Rise: 8>>3 = 1; Fall: 4>>3 = 0
    if(gpio == BUTTON1){
        programs[0]->button1ISR(state);
    }else if (gpio == BUTTON2){
        programs[0]->button2ISR(events>>3);
    }


}


int main(){

    clocks_init();
    stdio_init_all();

    printf("Hello World!\n");

    gpio_set_irq_enabled_with_callback(BUTTON1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,true,&button_isr);
    gpio_set_irq_enabled_with_callback(BUTTON2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,true,&button_isr);



    programs[0] = &scrollTextController;
    programs[0]->restart();


    ledMatrix.enableSubframes();



    scrollTextController.setColor(&color1, &color2);
    scrollTextController.setText(&text);




    while (true){

        uint32_t time = (timer_hw->timelr) / 1000;
        if(time-lastMillis > programs[0]->refreshSpeed || programs[0]->refreshSpeed == 0){
            lastMillis = time;
            programs[0]->refresh();


        }

    }
    return 0;

}



