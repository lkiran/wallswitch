#include <Arduino.h>
#include <stdint.h>
#include "RGB.h"

#ifndef RgbLed_h
#define RgbLed_h

class RgbLed
{
private:
	uint8_t redPin;
	uint8_t greenPin;
	uint8_t bluePin;
	
	uint8_t redChannel;
	uint8_t greenChannel;
	uint8_t blueChannel;
	RGB color;
	bool active = true;

	static uint8_t channel;
	static uint8_t newChannel();

	void driveLeds(RGB color);

public:
	RgbLed(const uint8_t redPin, const uint8_t greenPin, const uint8_t bluePin);

	void setColor(RGBA color);
	void setColor(RGB color);
	void turnOn();

	void turnOff();
	RGB getColor(void);
};

#endif