
#ifndef RgbLed_h
#define RgbLed_h

class RgbLed
{
public:
    class Color;
    RgbLed();
};

RgbLed::RgbLed()
{
}

class RgbLed::Color
{
public:
    Color(byte red = 0, byte green = 0, byte blue = 0, double alpha = 1)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }

private:
    byte red;
    byte green;
    byte blue;
    double alpha;
};

#endif