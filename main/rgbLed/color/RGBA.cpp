#include "RGBA.hpp"

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


