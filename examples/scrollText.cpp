#include <Arduino.h>
#include "hardware/pio.h"
#include "hardware/irq.h"

#include "PIOMatrixOutput/pio_matrix_output.h"
#include "PIOMatrixOutput/color.h"
#include "ScrollText/scroll_text.h"

#define BUTTON1 18
#define BUTTON2 19




Color frame[8][16];

PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);
ScrollText scrollText(&ledMatrix, &frame);

String text = "Hello World %H  ";

Color color1(1,0,0);
Color color2(0,0,0);




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



    scrollText.setColor(&color1, &color2);
    scrollText.setText(&text);




}




void loop() {
    scrollText.refresh();
    delay(100);


}


