#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include "pico/stdlib.h"
#endif

#include "hardware/watchdog.h"

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
#include "DisplayText/display_text.h"
#include "BrightnessControl/brightness_control.h"
#include "MeteoriteAnimation/meteorite_animation.h"

#include "Menu/menu_controller.h"
#include "Menu/menu_entry.h"

#define BUTTON1 18
#define BUTTON2 19

#define WATCHDOG_RESET_TIME 50
uint32_t lastWatchdogReset = 0;

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
RainbowAnimation rainbowAnimationFixed(&ledMatrix, &frame);
RainbowAnimation rainbowAnimationSmooth(&ledMatrix, &frame);
DisplayText displayText(&ledMatrix, &frame, &scrollText);
MeteoriteAnimation meteoriteAnimation(&ledMatrix, &frame);

BrightnessControl brightnessControl(&ledMatrix, &frame, &tinyText, &flash);

MenuController menuController(&staticText);
MenuEntry menuEntryAnimation;
MenuEntry menuEntryGame;
MenuEntry menuEntryText;
MenuEntry menuEntrySettings;



DisplayProgram *programs[2];




void button_isr(uint gpio, uint32_t events){
    uint8_t state = events>>3; // Rise: 8>>3 = 1; Fall: 4>>3 = 0
    switch (gpio){
        case BUTTON1:
            menuController.button1ISR(state);
            // programs[0]->button1ISR(state);
            break;
        case BUTTON2:
            menuController.button2ISR(state);
            // programs[0]->button2ISR(events>>3);
            break;
        default:
            break;
    }
}




void setup() {

    Serial.begin(115200);
    delay(2500); // Just so that the Serial Console has time to connect

    // Watchdog must be reset every 100 ms.
    // Watchdog is disabled when cores are in debug mode
    watchdog_enable(100, true);

    Serial.println("Hello World");




    gpio_set_irq_enabled_with_callback(BUTTON1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &button_isr);
    gpio_set_irq_enabled_with_callback(BUTTON2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &button_isr);

    // If no data is stored/Clean flash
    if(FlashController::readData(1) == nullptr){
        FlashController::eraseAllData();
        uint8_t data[] = {0,0,0,0};
        flash.writeData(1,data);
        flash.writeData(2,data);
        data[3] = 4;
        flash.writeData(3,data);
    }




    // Brightness
    brightnessControl.setBrightnessVar(&globalBrightness);
    brightnessControl.setBrightnessFlashKey(3);
    brightnessControl.loadBrightnessFromFlash();

    // Display programs settings
    rainbowAnimationFixed.setMode(fixed);
    rainbowAnimationSmooth.setMode(smooth);

    // Matrix settings
    ledMatrix.enableSubframes();



    // Menu settings - begin
    menuEntryText.addProgram(&displayText);
    menuEntryText.setName("1.%1Text");

    menuController.addNewEntry(&menuEntryText);



    menuEntryAnimation.addProgram(&fireworks);
    menuEntryAnimation.addProgram(&snake);
    menuEntryAnimation.addProgram(&gameOfLife);
    menuEntryAnimation.addProgram(&meteoriteAnimation);
    menuEntryAnimation.addProgram(&rainbowAnimationSmooth);
    menuEntryAnimation.addProgram(&rainbowAnimationFixed);
    menuEntryAnimation.addProgram(&fixedAnimation);

    menuEntryAnimation.setName("2.%1Animations");

    menuController.addNewEntry(&menuEntryAnimation);



    menuEntryGame.addProgram(&dinoGame);
    menuEntryGame.setName("3.%1Dino%2Game");

    menuController.addNewEntry(&menuEntryGame);


    menuEntrySettings.addProgram(&brightnessControl);
    menuEntrySettings.setName("4.%1Set%2Brightness");

    menuController.addNewEntry(&menuEntrySettings);



    menuEntryText.restart();
    // Menu settings - end








}




void loop() {

    menuController.loop();

    if(beo::millis() - lastWatchdogReset > WATCHDOG_RESET_TIME){
        lastWatchdogReset = beo::millis();
        watchdog_update();
    }

}



