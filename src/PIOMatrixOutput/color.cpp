//
// Created by leo on 03.04.24.
//

#include "color.h"

uint32_t globalBrightness = 4;

Color::Color(float red, float green, float blue) {
    this->red = calcFixedPointNumber(red);
    this->green = calcFixedPointNumber(green);
    this->blue = calcFixedPointNumber(blue);

}


uint16_t Color::checkAndReturnValid(uint16_t value) {
    if(value>MAX_COLOR_VALUE_RAW) return MAX_COLOR_VALUE_RAW;
    if(value<MIN_COLOR_VALUE) return MIN_COLOR_VALUE;
    return value;
}


uint32_t Color::calc() const {
    return ((toUint8(green) << 16) | (toUint8(red)  << 8) | toUint8(blue));
}

Color::Color() {
    red = 0;
    green = 0;
    blue = 0;
}


void Color::setRed(float value) {
    red = calcFixedPointNumber(value);
    red = checkAndReturnValid(red);

}

void Color::setGreen(float value) {
    green = calcFixedPointNumber(value);
    green = checkAndReturnValid(green);
}

void Color::setBlue(float value) {
    blue = calcFixedPointNumber(value);
    blue = checkAndReturnValid(blue);
}

void Color::setRedRaw(uint16_t value) {
    red = checkAndReturnValid(value);
}

void Color::setGreenRaw(uint16_t value) {
    green = checkAndReturnValid(value);
}

void Color::setBlueRaw(uint16_t value) {
    blue = checkAndReturnValid(value);
}



float Color::getRed() const {
    return calcFloatingPointNumber(red);
}

float Color::getGreen() const {
    return calcFloatingPointNumber(green);
}

float Color::getBlue() const {
    return calcFloatingPointNumber(blue);
}



uint16_t Color::getRedRaw() const {
    return red;
}

uint16_t Color::getGreenRaw() const {
    return green;
}

uint16_t Color::getBlueRaw() const {
    return blue;
}



void Color::set(Color *reference) {
    setRedRaw(reference->getRedRaw());
    setGreenRaw(reference->getGreenRaw());
    setBlueRaw(reference->getBlueRaw());
}

bool Color::equals(Color *reference) const {
    return red == reference->getRedRaw() && green == reference->getGreenRaw() && blue == reference->getBlueRaw();
}

void Color::add(Color *addition) {
    setRedRaw(red + addition->getRedRaw());
    setGreenRaw(green + addition->getGreenRaw());
    setBlueRaw(blue + addition->getBlueRaw());
}

void Color::multiply(float factor) {
    setRedRaw(uint16_t(float(red)*factor));
    setGreenRaw(uint16_t(float(green)*factor));
    setBlueRaw(uint16_t(float(blue)*factor));
}

void Color::average(Color *addition) {
    // calculate the avg color
    setRedRaw((red + addition->getRedRaw()) / 2);
    setGreenRaw((green + addition->getGreenRaw()) / 2);
    setBlueRaw((blue + addition->getBlueRaw()) / 2);
}

uint16_t Color::calcFixedPointNumber(float value) {

    // Actually relatively fast because the fraction is precompiled
    auto data = (uint16_t)(value * (float)uint16_t((((1 << (NORMAL_BITS+(uint8_t)log2(MAX_SUBFRAMES))) - 1) / ((1 << NORMAL_BITS) - 1))));

    return data;
}

float Color::calcFloatingPointNumber(uint16_t value) {
    // Actually relatively fast because the fraction is precompiled
    auto data = (float)((float)value / (float)uint16_t((((1 << (NORMAL_BITS+(uint8_t)log2(MAX_SUBFRAMES))) - 1) / ((1 << NORMAL_BITS) - 1))));
    return data;
}

uint8_t Color::toUint8(uint16_t value) {
    return value>>((uint8_t)log2(MAX_SUBFRAMES)) & 0xFF;
}

uint8_t Color::getNumberOfActiveSubframes(uint16_t value) {
    return value&((1 << ((uint8_t)log2(MAX_SUBFRAMES))) - 1);
}



uint16_t Color::getRed8Bit() const {
    return toUint8(red*globalBrightness/4);
}

uint16_t Color::getGreen8Bit() const {
    return toUint8(green*globalBrightness/4);
}

uint16_t Color::getBlue8Bit() const {
    return toUint8(blue*globalBrightness/4);
}


uint8_t Color::getRedActiveSubframes() const {
    return getNumberOfActiveSubframes(red*globalBrightness/4);
}

uint8_t Color::getGreenActiveSubframes() const {
    return getNumberOfActiveSubframes(green*globalBrightness/4);
}

uint8_t Color::getBlueActiveSubframes() const {
    return getNumberOfActiveSubframes(blue*globalBrightness/4);
}
















