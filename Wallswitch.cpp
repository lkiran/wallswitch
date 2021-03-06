#include "Wallswitch.h"

Wallswitch::Wallswitch(int pin, int activeLow, bool pullupActive)
	: OneButton(pin, activeLow, pullupActive)
{
}

Wallswitch::Wallswitch(String title, int pin, int activeLow, bool pullupActive)
	: title("/button/" + title), OneButton(pin, activeLow, pullupActive)
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
	this->haptic->poke();
}

void Wallswitch::handleClick()
{
	MqttConnection &mqttConnection = MqttConnection::instance();
	mqttConnection.publish(this->title, "clicked");
}

void Wallswitch::handleDoubleClick()
{
	MqttConnection &mqttConnection = MqttConnection::instance();
	mqttConnection.publish(this->title, "double-clicked");
}

void Wallswitch::handleLongPressStart()
{
	this->haptic->poke();
	MqttConnection &mqttConnection = MqttConnection::instance();
	mqttConnection.publish(this->title, "long-pressed");
}

// void Wallswitch::handleDuringLongPress()
// {
// }

void Wallswitch::handleLongPressStop()
{
}
