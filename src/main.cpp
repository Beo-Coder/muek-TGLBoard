#include <Arduino.h>
#include "hardware/pio.h"
#include "hardware/irq.h"

#include "pioMatrixOutput.h"
#include "scrollText.h"
#include "color.h"
#include "dinoGame.h"
#include "FireworkAnimation.h"


#define BUTTON1 18
#define BUTTON2 19

Color color1(1,0,0);
Color color2(0,0,0);


Color frame[8][16];

uint32_t lastMillis = 0;


PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);

scrollText scrollTextController(&ledMatrix, &frame);
DinoGame game(&ledMatrix, &frame);
FireworkAnimation fireworks(&ledMatrix, &frame);

display_program *programs[2];


String text = "Hello <W>orld!;   ";



void button1_isr() {
    programs[0]->button1ISR(digitalRead(BUTTON1));

}

void button2_isr() {
    programs[0]->button2ISR(digitalRead(BUTTON2));



}




void setup() {
    delay(3500); // Just so that the Serial Console has time to connect
    programs[0] = &fireworks;
    scrollTextController.setText(&text);
    scrollTextController.setColor(&color1,&color2);
    Serial.begin(115200);

    Serial.println("Hello World");


    pinMode(BUTTON1, INPUT_PULLDOWN);
    pinMode(BUTTON2, INPUT_PULLDOWN);

    attachInterrupt(digitalPinToInterrupt(18), button1_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(19), button2_isr, CHANGE);



    color1.setRed(0.5);
    color1.setGreen(0);
    color1.setBlue(0);

    color1.setBrightness(10);



    color2.setRed(0);
    color2.setGreen(0);
    color2.setBlue(0);



    //ledMatrix.setFrameBufferInterval(90);
    //ledMatrix.enableFrameBuffer();
    ledMatrix.enableSubframes();



    // scrollTextController.setColor(&color1, &color2);
    // scrollTextController.setText(&text);




}




void loop() {
/*
    while(millis()-lastMillis > 220){
        lastMillis = millis();

        for(int i=0; i<MATRIX_HEIGHT; i++){
            for(int j=0; j<MATRIX_LENGTH; j++){
                frame[i][j] = color1;
            }
        }
        ledMatrix.setDisplayData(&frame);
        ledMatrix.sendData();



        // Serial.println(game.score);
        //programs[0]->refresh();

    }*/


    while(millis()-lastMillis > programs[0]->refreshSpeed){
        lastMillis = millis();
        // Serial.println(game.score);
        programs[0]->refresh();

    }



}
