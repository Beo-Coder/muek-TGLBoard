#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif


#include "beo_common.h"

#include "PIOMatrixOutput/pio_matrix_output.h"

#include "FlashController/flash_controller.h"

#include "TextController/scroll_text.h"
#include "TextController//static_text.h"
#include "TextController/tiny_text.h"


#include "DinoGame/dinoGame.h"
#include "Firework/firework_animation.h"
#include "TetrisGame/tetris.h"
#include "SnakeAI/snake_ai_animation.h"
#include "GameOfLife/game_of_life_animation.h"
#include "FixedAnimation/fixed_animation.h"
#include "RainbowAnimation/rainbow_animation.h"


#define BUTTON1 18
#define BUTTON2 19

Color color1(1,0,0);
Color color3(0,1,0);
Color color2(0,0,0);


Color frame[8][16];

uint32_t lastMillis = 0;


PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);

FlashController flash;

ScrollText scrollText(&ledMatrix, &frame);
StaticText staticText(&ledMatrix, &frame);
TinyText tinyText(&ledMatrix, &frame);


DinoGame dinoGame(&ledMatrix, &frame, &staticText, &flash);
FireworkAnimation fireworks(&ledMatrix, &frame);
Tetris tetrisGame(&ledMatrix, &frame, &staticText, &flash);
SnakeAI snake(&ledMatrix, &frame);
GameOfLife gameOfLife(&ledMatrix, &frame);
FixedAnimation fixedAnimation(&ledMatrix, &frame);
RainbowAnimation rainbowAnimation(&ledMatrix, &frame);



DisplayProgram *programs[2];


std::string text = "Hello World!  ";




void button_isr(uint gpio, uint32_t events){
    uint8_t state = events>>3; // Rise: 8>>3 = 1; Fall: 4>>3 = 0
    switch (gpio){
        case BUTTON1:
            programs[0]->button1ISR(state);
            break;
        case BUTTON2:
            programs[0]->button2ISR(events>>3);
            break;
        default:
            break;
    }
}




void setup() {
    Serial.begin(115200);
    delay(2500); // Just so that the Serial Console has time to connect
    Serial.println("Hello World");

    gpio_set_irq_enabled_with_callback(BUTTON1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &button_isr);
    gpio_set_irq_enabled_with_callback(BUTTON2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &button_isr);

    // If no data is stored/Clean flash
    if(FlashController::readData(1) == nullptr){
        FlashController::eraseAllData();
        uint8_t data[] = {0,0,0,0};
        flash.writeData(1,data);
        flash.writeData(2,data);
    }

    ledMatrix.enableSubframes();

    programs[0] = &rainbowAnimation;
    programs[0]->restart();

    staticText.setColor(&color1, &color2);
    staticText.setText(&text);



}




void loop() {



    if(beo::millis()-lastMillis > programs[0]->refreshSpeed || programs[0]->refreshSpeed == 0){
        lastMillis = beo::millis();
        programs[0]->refresh();

    }


}


