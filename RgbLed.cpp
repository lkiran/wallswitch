#include "RgbLed.h"

int RgbLed::channel = 3; // Channel must be in range of 0-16

void RgbLed::driveLeds(RGB color)
{
	if (this->redPin)
	{
		ledcWrite(this->redChannel, 256 - color.getRed());
	}

	if (this->greenPin)
	{
		ledcWrite(this->greenChannel, 256 - color.getGreen());
	}

	if (this->bluePin)
	{
		ledcWrite(this->blueChannel, 256 - color.getBlue());
	}
}

RgbLed::RgbLed(int redPin, int greenPin, int bluePin)
{
	this->redPin = redPin;
	this->greenPin = greenPin;
	this->bluePin = bluePin;

	if (this->redPin > 0)
	{
		this->redChannel = RgbLed::newChannel();
		pinMode(this->redPin, OUTPUT);
		ledcAttachPin(redPin, this->redChannel); // assign led pin to channel
		ledcSetup(this->redChannel, 12000, 8);	 // 12 kHz PWM, 8-bit resolution
	}

	if (this->greenPin > 0)
	{
		this->greenChannel = RgbLed::newChannel();
		pinMode(this->greenPin, OUTPUT);
		ledcAttachPin(greenPin, this->greenChannel);
		ledcSetup(this->greenChannel, 12000, 8);
	}

	if (this->bluePin > 0)
	{
		this->blueChannel = RgbLed::newChannel();
		pinMode(this->bluePin, OUTPUT);
		ledcAttachPin(bluePin, this->blueChannel);
		ledcSetup(this->blueChannel, 12000, 8);
	}
}

int RgbLed::newChannel()
{
	RgbLed::channel++;
	return RgbLed::channel;
}

void RgbLed::setColor(RGBA color)
{
	this->setColor(color.toRGB());
}

void RgbLed::setColor(RGB color)
{
	this->driveLeds(color);
	this->color = color;
}

void RgbLed::turnOn()
{
	this->active = true;
	this->setColor(this->color);
}

void RgbLed::turnOff()
{
	this->active = false;
	this->driveLeds(RGB::black);
}

RGB RgbLed::getColor(void)
{
	return this->color;
}