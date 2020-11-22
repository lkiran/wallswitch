#include "LedCallback.h"

LedCallback::LedCallback(RgbLed &led) : _led(led)
{
}

void LedCallback::handle(String topic, String payload)
{
    RGB color(payload);
    this->_led.setColor(color);
}