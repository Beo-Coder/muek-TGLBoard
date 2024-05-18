//
// Created by leo on 03.04.24.
//

#include "color.h"


Color::Color(float red, float green, float blue) {
    this->red = checkAndReturnValid(red);
    this->green = checkAndReturnValid(green);
    this->blue = checkAndReturnValid(blue);
    brightness = 1;

}


float Color::checkAndReturnValid(float value) {
    if(value>MAX_COLOR_VALUE){
        return MAX_COLOR_VALUE;
    }
    if(value<MIN_COLOR_VALUE){
        return MIN_COLOR_VALUE;
    }
    return value;
}


uint32_t Color::calc() {


    return ((uint8_t)(green*brightness) << 16) | ((uint8_t)(red*brightness) << 8) | ((uint8_t)(blue*brightness));

}

Color::Color() {
    red = 0;
    green = 0;
    blue = 0;
    brightness = NORMAL_BRIGHTNESS;

}

void Color::setBrightness(float value) {
    if(value < MIN_BRIGHTNESS){
        brightness = MIN_BRIGHTNESS;
    }else if (value > MAX_BRIGHTNESS) {
        brightness = MAX_BRIGHTNESS;
    }else{
            brightness = value;
    }



}

float Color::getBrightness() {
    return brightness;
}



void Color::setRed(float value) {
    red = checkAndReturnValid(value);

}

void Color::setGreen(float value) {
    green = checkAndReturnValid(value);
}

void Color::setBlue(float value) {
    blue = checkAndReturnValid(value);
}



float Color::getRed(bool raw) {
    return red*(brightness*float((1-raw)));
}

float Color::getGreen(bool raw) {
    return green*(brightness*float((1-raw)));
}

float Color::getBlue(bool raw) {
    return blue*(brightness*float((1-raw)));
}

void Color::setRGB(uint8_t colorNumber, float value) {
    switch (colorNumber) {
        case 0:
            setRed(value);
            break;
        case 1:
            setGreen(value);
            break;
        case 2:
            setBlue(value);
            break;
    }

}



float Color::getRGB(uint8_t colorNumber, bool raw) {
    switch (colorNumber) {
        case 0:
            getRed(raw);
            break;
        case 1:
            getGreen(raw);
            break;
        case 2:
            getBlue(raw);
            break;
        default:
            return -1;
    }
    return -1;
}

void Color::set(Color *reference) {
    setRed(reference->red);
    setGreen(reference->green);
    setBlue(reference->blue);
}

bool Color::equals(Color *reference) {
    return red == reference->red && green == reference->green && blue == reference->blue;
}

void Color::add(Color *addition) {
    // if the value overflows max value will be used
    if (red + addition->red >= MAX_COLOR_VALUE) {
        setRed(MAX_COLOR_VALUE);
    } else {
        setRed(red + addition->red);
    }
    if (green + addition->green >= MAX_COLOR_VALUE) {
        setGreen(MAX_COLOR_VALUE);
    } else {
        setGreen(green + addition->green);
    }
    if (blue + addition->blue >= MAX_COLOR_VALUE) {
        setBlue(MAX_COLOR_VALUE);
    } else {
        setBlue(blue + addition->blue);
    }
}

void Color::multiply(float factor) {
    setRed(red * factor);
    setGreen(green * factor);
    setBlue(green * factor);
}

void Color::average(Color *addition) {
    // calculate the avg color
    setRed((red + addition->red) /2);
    setGreen((green + addition->green) /2);
    setBlue((blue + addition->blue) /2);
}









