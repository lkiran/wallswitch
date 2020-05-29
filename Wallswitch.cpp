#include "Wallswitch.h"

Wallswitch::Wallswitch(int pin, int activeLow, bool pullupActive)
	: OneButton(pin, activeLow, pullupActive)
{
	Serial.println("Wallswitch");
}

void Wallswitch::setHaptic(HapticFeedback *haptic)
{
	Serial.println("Wallswitch::setHaptic");
	this->haptic = haptic;
}

void Wallswitch::setLed(RgbLed *led)
{
	Serial.println("Wallswitch::setLed");
	this->led = led;
}

void Wallswitch::handlePress()
{
	Serial.println(this->getPin());
	Serial.println(" handlePress");
}

void Wallswitch::handleClick()
{
	Serial.println(this->getPin());
	Serial.println(" handleClick");
	if (this->led->getColor() == RGB::blue)
		this->led->setColor(RGB::cyan);
	else
		this->led->setColor(RGB::blue);
}

void Wallswitch::handleDoubleClick()
{
	Serial.println(this->getPin());
	Serial.println(" handleDoubleClick");
	this->haptic->poke();
	this->haptic->poke();
	if (this->led->getColor() == RGB::green)
		this->led->setColor(RGB::yellow);
	else
		this->led->setColor(RGB::green);
}

void Wallswitch::handleLongPressStart()
{
	Serial.println(this->getPin());
	Serial.println(" handleLongPressStart");
	this->haptic->poke();
	if (this->led->getColor() == RGB::red)
		this->led->setColor(RGB::magenta);
	else
		this->led->setColor(RGB::red);
}

// void Wallswitch::handleDuringLongPress()
// {
//    Serial.println(this->getPin());
//    Serial.println(" handleDuringLongPress");
// }

void Wallswitch::handleLongPressStop()
{
	Serial.println(this->getPin());
	Serial.println(" handleLongPressStop");
}
