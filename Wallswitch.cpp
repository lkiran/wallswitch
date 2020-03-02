#include "Wallswitch.h"

Wallswitch::Wallswitch(int pin, int activeLow, bool pullupActive)
    : OneButton(pin, activeLow, pullupActive)
{
}

void Wallswitch::setHaptic(HapticFeedback haptic)
{
    this->haptic = haptic;
}

void Wallswitch::handleClick()
{
    haptic.poke();
}
