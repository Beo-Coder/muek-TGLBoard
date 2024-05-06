#include <Arduino.h>
#include "hardware/pio.h"
#include "hardware/irq.h"

#include "PIOMatrixOutput/pio_matrix_output.h"
#include "color.h"

#define BUTTON1 18
#define BUTTON2 19

Color color1(1,0,0);
Color color2(0,0,0);


Color frame[8][16];

PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);






void button1_isr() {

}

void button2_isr() {

}




void setup() {
    Serial.begin(115200);
    delay(3500); // Just so that the Serial Console has time to connect


    Serial.println("Hello World");


    pinMode(BUTTON1, INPUT_PULLDOWN);
    pinMode(BUTTON2, INPUT_PULLDOWN);

    attachInterrupt(digitalPinToInterrupt(18), button1_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(19), button2_isr, CHANGE);


    ledMatrix.enableSubframes();
    ledMatrix.enableFrameBuffer();
    ledMatrix.setFrameBufferInterval(100);

    // 5 different major color steps with 4 subframes each
    for(int brightness=0; brightness<=5*4;brightness++){
        color1.setRed(float(brightness)/4);
        for(int i=0;i<MATRIX_HEIGHT;i++){
            for(int j=0;j<MATRIX_LENGTH;j++){
                frame[i][j] = color1;
            }
        }

        if(ledMatrix.getFreeFrames()<1){
            Serial.println("Framebuffer is currently full. Waiting");
        }
        while(ledMatrix.getFreeFrames()<1);
        ledMatrix.addToFrameBuffer(&frame);
        Serial.println("Added frame to framebuffer");
    }
    Serial.println("All frames added");





}




void loop() {
    tight_loop_contents();


}


