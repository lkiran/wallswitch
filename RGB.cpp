#include "RGB.h"

RGB::RGB()
{
}

RGB::RGB(const uint8_t red = 0, const uint8_t green = 0, const uint8_t blue = 0)
{
	this->redValue = red;
	this->greenValue = green;
	this->blueValue = blue;
}

uint8_t RGB::getRed()
{
	return this->redValue;
}

uint8_t RGB::getGreen()
{
	return this->greenValue;
}

uint8_t RGB::getBlue()
{
	return this->blueValue;
}

bool RGB::operator==(const RGB &rhs) const
{
	if (this->redValue != rhs.redValue || this->greenValue != rhs.greenValue || this->blueValue != rhs.blueValue)
		return false;

	return true;
}

bool RGB::operator!=(const RGB &rhs) const
{
	if (this->redValue == rhs.redValue && this->greenValue == rhs.greenValue && this->blueValue == rhs.blueValue)
		return false;

	return true;
}

RGBA::RGBA(RGB color) : RGB(color)
{
	this->alpha = 1;
}

RGBA::RGBA(const uint8_t red = 0, const uint8_t green = 0, const uint8_t blue = 0, const double alpha = 1) : RGB(red, green, blue)
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