#include "RGB.h"

RGB::RGB()
{
}

RGB::RGB(int red = 0, int green = 0, int blue = 0)
{
    this->redValue = red;
    this->greenValue = green;
    this->blueValue = blue;
}

int RGB::getRed()
{
    return this->redValue;
}

int RGB::getGreen()
{
    return this->greenValue;
}

int RGB::getBlue()
{
    return this->blueValue;
}

RGBA::RGBA(RGB color) : RGB(color)
{
    this->alpha = 1;
}

RGBA::RGBA(int red = 0, int green = 0, int blue = 0, double alpha = 1) : RGB(red, green, blue)
{
    this->alpha = alpha;
}

RGB RGBA::toRGB(void)
{
    return RGB(this->redValue * this->alpha, this->greenValue * this->alpha, this->blueValue * this->alpha);
}

RGB RGB::white(255, 255, 255);
RGB RGB::red(255, 0, 0);
RGB RGB::green(0, 255, 0);
RGB RGB::blue(0, 0, 255);
RGB RGB::cyan(0, 255, 255);
RGB RGB::magenta(255, 0, 255);
RGB RGB::yellow(255, 255, 0);
RGB RGB::black(0, 0, 0);