
#ifndef RgbLed_h
#define RgbLed_h

#include <Arduino.h>
#include <stdint.h>
#include "RGB.h"

class RgbLed
{
private:
	int redPin;
	int greenPin;
	int bluePin;
	
	int redChannel;
	int greenChannel;
	int blueChannel;
	RGB color;
	bool active = true;

	static int channel;
	static int newChannel();

	void driveLeds(RGB color);

public:
	RgbLed(int redPin, int greenPin, int bluePin);

	void setColor(RGBA color);
	void setColor(RGB color);
	void turnOn();

	void turnOff();
	RGB getColor(void);
};

#endif