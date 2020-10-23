#ifndef MqttCallback_h
#define MqttCallback_h

#include "Arduino.h"
#include "RgbLed.h"

class MqttCallback
{
public:
    MqttCallback();
    void setName(String name);
    void handle(String topic, String payload);

private:
};

#endif
