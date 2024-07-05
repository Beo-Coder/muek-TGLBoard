//
// © 2024 Leonhard Baschang
//

#include <Arduino.h>


#include "FlashController/flash_controller.h"




FlashController flash;



void setup() {
    Serial.begin(115200);
    delay(3500); // Just so that the Serial Console has time to connect
    Serial.println("Hello World");





    // Access Key 1 has four bytes of data

    // Get start address for access key 1
    Serial.print("Read begin");
    uint8_t *p = flash.readData(1);
    Serial.print("Read done");

    uint8_t data = 0;



    // Read for access Key 1 four bytes of data
    Serial.print("Read data: ");
    for(int i=0; i<4; i++){
        if(p != nullptr){
            data = *(p+i);
        }
        Serial.print(data, HEX);
        Serial.print(" ");
    }

    Serial.print("\n\r");
    Serial.print("Read address: ");
    Serial.print((uint32_t) p);
    Serial.print("\n\r");


    // Write for access key 1 four bytes of data
    uint8_t writeData[4] = {0x14,0x11,0x20,0x04};
    Serial.println("Write data");
    Serial.println(flash.writeData(1, writeData));
    Serial.println("Write data done");


}




void loop() {
    tight_loop_contents();
}


