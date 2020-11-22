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

RGB::RGB(String code)
{
	long long number = strtoll(&code[1], NULL, 16);

	this->redValue = number >> 16;
	this->greenValue = number >> 8 & 0xFF;
	this->blueValue = number & 0xFF;
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

RGBA::RGBA(int red = 0, int green = 0, int blue = 0, double alpha = 1) : RGB(red, green, blue)
{
	this->alpha = alpha;
}

RGB RGBA::toRGB(void)
{
	return RGB(this->redValue * this->alpha, this->greenValue * this->alpha, this->blueValue * this->alpha);
}

RGB RGB::white(150, 150, 150);
RGB RGB::red(150, 0, 0);
RGB RGB::green(0, 150, 0);
RGB RGB::blue(0, 0, 150);
RGB RGB::cyan(0, 150, 150);
RGB RGB::magenta(150, 0, 150);
RGB RGB::yellow(150, 150, 0);
RGB RGB::black(0, 0, 0);