#include <Arduino.h>
#include "hardware/pio.h"
#include "hardware/irq.h"
#include "pioMatrixOutput.h"
#include "scrollText.h"
#include "color.h"


#define BUTTON1 18
#define BUTTON2 19

Color color1;
Color color2;


Color frame[8][16];


PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);

scrollText scrollTextController(&ledMatrix);

String text = "TGL Board WOW Muk is cool best Muk ever     ";



void button1_isr() {

}

void button2_isr() {

}


void setup() {
    delay(3500); // Just so that the Serial Console has time to connect
    Serial.begin(115200);

    Serial.println("Hello World");


    pinMode(BUTTON1, INPUT_PULLDOWN);
    pinMode(BUTTON2, INPUT_PULLDOWN);

    attachInterrupt(digitalPinToInterrupt(18), button1_isr, RISING);
    attachInterrupt(digitalPinToInterrupt(19), button2_isr, RISING);


    color1.red = 10;
    color1.green = 0.25;
    color1.blue = 0.25;

    color2.red = 0;
    color2.green = 0;
    color2.blue = 0;


    ledMatrix.setFrameBufferInterval(90);
    ledMatrix.enableFrameBuffer();
    ledMatrix.enableSubframes();

    scrollTextController.setColor(&color1, &color2);
    scrollTextController.setText(&text);

}


void loop() {

    if(ledMatrix.getFreeFrames() > 1){

        scrollTextController.shiftText();

    }




}
