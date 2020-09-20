#include "Wallswitch.h"

Wallswitch::Wallswitch(int pin, int activeLow, bool pullupActive)
	: OneButton(pin, activeLow, pullupActive)
{
}

void Wallswitch::setHaptic(HapticFeedback *haptic)
{
	this->haptic = haptic;
}

void Wallswitch::setLed(RgbLed *led)
{
	this->led = led;
}

void Wallswitch::handlePress()
{
}

void Wallswitch::handleClick()
{
	if (this->led->getColor() == RGB::blue)
		this->led->setColor(RGB::cyan);
	else
		this->led->setColor(RGB::blue);
}

void Wallswitch::handleDoubleClick()
{
	this->haptic->poke();
	this->haptic->poke();
	if (this->led->getColor() == RGB::green)
		this->led->setColor(RGB::yellow);
	else
		this->led->setColor(RGB::green);
}

void Wallswitch::handleLongPressStart()
{
	this->haptic->poke();
	if (this->led->getColor() == RGB::red)
		this->led->setColor(RGB::magenta);
	else
		this->led->setColor(RGB::red);
}

// void Wallswitch::handleDuringLongPress()
// {
// }

void Wallswitch::handleLongPressStop()
{

}
