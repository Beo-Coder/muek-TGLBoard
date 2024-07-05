//
// © 2024 Leonhard Baschang
//

#include <Arduino.h>

#include "PIOMatrixOutput/pio_matrix_output.h"

#define BUTTON1 18
#define BUTTON2 19

Color color1(1,0,0);
Color color2(0,0,0);


Color frame[8][16];

PIO pio = pio0;


MatrixOutput ledMatrix(pio, 0, 0, 10, 11);






void setup() {
    Serial.begin(115200);
    delay(3500); // Just so that the Serial Console has time to connect


    Serial.println("Hello World");



    ledMatrix.enableSubframes();
    color1.setRed(0.25);

    for(int i=0;i<MATRIX_HEIGHT;i++){
        for(int j=0;j<MATRIX_LENGTH;j++){
            frame[i][j] = color1;

        }
    }
    ledMatrix.setDisplayData(&frame);
    ledMatrix.sendData();




}




void loop() {
    tight_loop_contents();


}


