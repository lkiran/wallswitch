#include "LedCallback.h"

LedCallback::LedCallback(RgbLed &led) : _led(led)
{
    Serial.println("LedCallback ctor");
}

void LedCallback::handle(String topic, String payload)
{
    Serial.println("LedCallback::handle " + payload);
    RGB color(payload);
    this->_led.setColor(color);
}