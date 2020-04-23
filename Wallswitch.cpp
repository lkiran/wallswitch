#include "Wallswitch.h"

Wallswitch::Wallswitch(int pin, int activeLow, bool pullupActive)
    : OneButton(pin, activeLow, pullupActive)
{
    Serial.println("Wallswitch");
}

void Wallswitch::setHaptic(HapticFeedback haptic)
{
    this->haptic = haptic;
}

void Wallswitch::setLed(RgbLed led)
{
    this->led = led;
}

void Wallswitch::handleClick()
{
    haptic.poke();
}

void Wallswitch::handleDoubleClick()
{
    haptic.poke();
}

void Wallswitch::handleLongPressStart()
{
    haptic.poke();
}
