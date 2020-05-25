#include <Arduino.h>
#include "RGB.h"

#ifndef RgbLed_h
#define RgbLed_h

class RgbLed
{
private:
	byte redPin;
	byte greenPin;
	byte bluePin;
	RGB color;
	bool active = true;

	static int channel;

	void driveLeds(RGB color);

public:
	RgbLed();
	RgbLed(byte redPin, byte greenPin, byte bluePin);

	void setColor(RGBA color);
	void setColor(RGB color);
	void turnOn();

	void turnOff();
	RGB getColor(void);
};

#endif