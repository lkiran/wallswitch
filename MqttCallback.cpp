#include "MqttCallback.h"

MqttCallback::MqttCallback() {}

void MqttCallback::handle(String topic, String payload)
{
    Serial.print("payload: ");
    Serial.println(payload);
}