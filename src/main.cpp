#include <Arduino.h>

#include "PIOMatrixOutput/pio_matrix_output.h"

#include "TextController/scroll_text.h"
#include "TextController//static_text.h"
#include "TextController/tiny_text.h"


#include "DinoGame/dinoGame.h"
#include "Firework/firework_animation.h"
#include "TetrisGame/tetris.h"
#include "SnakeAI/snake_ai_animation.h"





#define BUTTON1 18
#define BUTTON2 19

Color color1(1,0,0);
Color color3(0,1,0);
Color color2(0,0,0);


Color frame[8][16];

uint32_t lastMillis = 0;


PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);

ScrollText scrollText(&ledMatrix, &frame);
StaticText staticText(&ledMatrix, &frame);
TinyText tinyText(&ledMatrix, &frame);


DinoGame dinoGame(&ledMatrix, &frame);
FireworkAnimation fireworks(&ledMatrix, &frame);
Tetris tetrisGame(&ledMatrix, &frame, &staticText);
SnakeAI snake(&ledMatrix, &frame);




display_program *programs[2];


String text = "Hello%nWorld";




void button1_isr() {
    programs[0]->button1ISR(digitalRead(BUTTON1));

}

void button2_isr() {
    programs[0]->button2ISR(digitalRead(BUTTON2));



}




void setup() {
    Serial.begin(115200);
    delay(3500); // Just so that the Serial Console has time to connect
    Serial.println("Hello World");

    pinMode(BUTTON1, INPUT_PULLDOWN);
    pinMode(BUTTON2, INPUT_PULLDOWN);

    attachInterrupt(digitalPinToInterrupt(18), button1_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(19), button2_isr, CHANGE);




    programs[0] = &fireworks;
    programs[0]->restart();

    tinyText.setColor(&color1, &color3, &color2);
    tinyText.setText(&text);




    ledMatrix.enableSubframes();




}




void loop() {



    if(millis()-lastMillis > programs[0]->refreshSpeed || programs[0]->refreshSpeed == 0){
        lastMillis = millis();
        programs[0]->refresh();

    }


}


