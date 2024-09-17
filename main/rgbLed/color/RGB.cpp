#include "RGB.hpp"

RGB::RGB() {
}

RGB::RGB(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0) : redValue(red), greenValue(green), blueValue(blue) {
}

RGB::RGB(string code) {
    long long number;
    if (code.length() == 6)
        number = strtoll(&code[0], nullptr, 16);
    else if (code.length() == 7)
        number = strtoll(&code[1], nullptr, 16);
    else
        return;

    this->redValue = number >> 16;
    this->greenValue = number >> 8 & 0xFF;
    this->blueValue = number & 0xFF;
}

uint8_t RGB::getRed() {
    return this->redValue;
}

uint8_t RGB::getGreen() {
    return this->greenValue;
}

uint8_t RGB::getBlue() {
    return this->blueValue;
}

bool RGB::operator==(const RGB &rhs) const {
    if (this->redValue != rhs.redValue || this->greenValue != rhs.greenValue || this->blueValue != rhs.blueValue)
        return false;

    return true;
}

bool RGB::operator!=(const RGB &rhs) const {
    if (this->redValue == rhs.redValue && this->greenValue == rhs.greenValue && this->blueValue == rhs.blueValue)
        return false;

    return true;
}

RGB RGB::white(150, 150, 150);
RGB RGB::red(150, 0, 0);
RGB RGB::green(0, 150, 0);
RGB RGB::blue(0, 0, 150);
RGB RGB::cyan(0, 150, 150);
RGB RGB::magenta(150, 0, 150);
RGB RGB::yellow(150, 150, 0);
RGB RGB::black(0, 0, 0);
