#ifndef RgbLed_h
#define RgbLed_h
#include "RGB.h"

class RgbLed
{
private:
	byte redPin;
	byte greenPin;
	byte bluePin;
	RGB color;
	bool active = true;

	void driveLeds(RGB color)
	{
		Serial.println("RgbLed::driveLeds");
		if (this->redPin)
		{
			Serial.print("ledcWrite(");
			Serial.print(1);
			Serial.print(", ");
			Serial.print(color.getRed());
			Serial.println(");");
			ledcWrite(1, color.getRed());
		}

		if (this->greenPin)
		{
			Serial.print("ledcWrite(");
			Serial.print(2);
			Serial.print(", ");
			Serial.print(color.getGreen());
			Serial.println(");");
			ledcWrite(2, color.getGreen());
		}

		if (this->bluePin)
		{
			Serial.print("ledcWrite(");
			Serial.print(3);
			Serial.print(", ");
			Serial.print(color.getBlue());
			Serial.println(");");
			ledcWrite(3, color.getBlue());
		}
		Serial.println("RgbLed::driveLeds completed");
	}

public:
	RgbLed()
	{
	}

	RgbLed(byte redPin, byte greenPin, byte bluePin)
	{
		Serial.println("RgbLed start");
		this->redPin = redPin;
		this->greenPin = greenPin;
		this->bluePin = bluePin;

		if (this->redPin)
		{
			pinMode(this->redPin, OUTPUT);
			ledcAttachPin(redPin, 1); // assign led pin to channel
			ledcSetup(1, 12000, 8);	  // 12 kHz PWM, 8-bit resolution
		}

		if (this->greenPin)
		{
			pinMode(this->greenPin, OUTPUT);
			ledcAttachPin(greenPin, 2);
			ledcSetup(2, 12000, 8);
		}

		if (this->bluePin)
		{
			pinMode(this->bluePin, OUTPUT);
			ledcAttachPin(bluePin, 3);
			ledcSetup(3, 12000, 8);
		}
		Serial.println("RgbLed end");
	}

	void setColor(RGBA color)
	{
		this->setColor(color.toRGB());
	}

	void setColor(RGB color)
	{
		Serial.println("RgbLed::setColor");
		this->driveLeds(color);
		this->color = color;
		Serial.println("RgbLed::setColor completed");
	}

	void turnOn()
	{
		this->active = true;
		this->setColor(this->color);
	}

	void turnOff()
	{
		this->active = false;
		this->driveLeds(black);
	}

	RGB getColor(void)
	{
		return this->color;
	}
};

#endif