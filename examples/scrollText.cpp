#include <Arduino.h>

#include "PIOMatrixOutput/pio_matrix_output.h"
#include "TextController//scroll_text.h"

#define BUTTON1 18
#define BUTTON2 19




Color frame[8][16];

PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);
ScrollText scrollText(&ledMatrix, &frame);

std::string text = "Hello World %H  ";

Color color1(1,0,0);
Color color2(0,0,0);




void setup() {
    Serial.begin(115200);
    delay(3500); // Just so that the Serial Console has time to connect


    Serial.println("Hello World");


    scrollText.setColor(&color1, &color2);
    scrollText.setText(&text);




}




void loop() {
    scrollText.refresh();
    delay(100);


}


