#ifndef LedCallback_h
#define LedCallback_h

#include "MqttCallback.h"
#include "RgbLed.h"
#include "RGB.h"

class LedCallback : public MqttCallback
{
private:
    RgbLed &_led;

public:
    LedCallback(RgbLed &led);
    void handle(String topic, String payload);
};

#endif