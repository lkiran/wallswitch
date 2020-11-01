#ifndef MqttCallback_h
#define MqttCallback_h

#include "Arduino.h"

class MqttCallback
{
public:
    MqttCallback() = default;
    virtual void handle(String topic, String payload) = 0;
};

#endif
