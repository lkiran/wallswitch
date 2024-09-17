#pragma once

#include <string>
#include "led_convert.h"

using namespace std;

extern "C"
class RGB {
public:
    RGB();

    explicit RGB(string code);

    RGB(uint8_t red, uint8_t green, uint8_t blue);

    bool operator==(const RGB &rhs) const;

    bool operator!=(const RGB &rhs) const;

    uint8_t getRed();

    uint8_t getGreen();

    uint8_t getBlue();

    static RGB white;
    static RGB red;
    static RGB green;
    static RGB blue;
    static RGB cyan;
    static RGB magenta;
    static RGB yellow;
    static RGB black;

protected:
    uint8_t redValue;
    uint8_t greenValue;
    uint8_t blueValue;
};

