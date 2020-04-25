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

void Wallswitch::setLed(RgbLed led)
{
    this->led = led;
}

void Wallswitch:: handlePress()
{
   Serial.println(this->getPin());
   Serial.println(" handlePress");
}

void Wallswitch::handleClick()
{
   Serial.println(this->getPin());
   Serial.println(" handleClick");
}

void Wallswitch::handleDoubleClick()
{
   Serial.println(this->getPin());
   Serial.println(" handleDoubleClick");
   this->haptic->poke();
   this->haptic->poke();
}

void Wallswitch::handleLongPressStart()
{
   Serial.println(this->getPin());
   Serial.println(" handleLongPressStart");
   this->haptic->poke();
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
