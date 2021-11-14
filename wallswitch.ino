#include "Wallswitch.h"
#include "WallswitchWiFiObserver.h"
#include "HapticFeedback.h"
#include "RgbLed.h"
#include "TempreratureSensor.h"
#include "WiFiConnection.h"
#include "MqttConnection.h"
#include "LedCallback.h"

TempreratureSensor tempreratureSensor(26);
HapticFeedback hapticFeedback(23);

RgbLed rgbLedTopLeft(18, 5, 17);
RgbLed rgbLedTopRight(25, 33, 32);
RgbLed rgbLedBottomLeft(4, 16, 2);
RgbLed rgbLedBottomRight(12, 14, 27);

Wallswitch buttonTopLeft("top-left", 19, false);
Wallswitch buttonTopRight("top-right", 35, false);
Wallswitch buttonBottomLeft("bottom-left", 15, false);
Wallswitch buttonBottomRight("bottom-right", 13, false);

WiFiConnection &wifiConnection = WiFiConnection::instance();
MqttConnection &mqttConnection = MqttConnection::instance();

void setup()
{
	Serial.begin(115200);
	Serial.println("---------------starting setup---------------");
	
	rgbLedTopLeft.setColor(RGB::black);
	rgbLedTopRight.setColor(RGB::black);
	rgbLedBottomLeft.setColor(RGB::black);
	rgbLedBottomRight.setColor(RGB::black);

	buttonTopLeft.setHaptic(&hapticFeedback);
	buttonTopRight.setHaptic(&hapticFeedback);
	buttonBottomLeft.setHaptic(&hapticFeedback);
	buttonBottomRight.setHaptic(&hapticFeedback);

	buttonTopLeft.setLed(&rgbLedTopLeft);
	buttonTopRight.setLed(&rgbLedTopRight);
	buttonBottomLeft.setLed(&rgbLedBottomLeft);
	buttonBottomRight.setLed(&rgbLedBottomRight);

	WallswitchWiFiObserver(wifiConnection, rgbLedTopLeft);
	wifiConnection.connect("KIRAN", "altintas");

	mqttConnection.configure("10.0.0.51");
	mqttConnection.connect();

	static LedCallback ledCallbackTopLeft = LedCallback(rgbLedTopLeft);
	static LedCallback ledCallbackTopRight = LedCallback(rgbLedTopRight);
	static LedCallback ledCallbackBottomLeft = LedCallback(rgbLedBottomLeft);
	static LedCallback ledCallbackBottomRight = LedCallback(rgbLedBottomRight);
	mqttConnection.subscribe("/led/top-left", &ledCallbackTopLeft);
	mqttConnection.subscribe("/led/top-right", &ledCallbackTopRight);
	mqttConnection.subscribe("/led/bottom-left", &ledCallbackBottomLeft);
	mqttConnection.subscribe("/led/bottom-right", &ledCallbackBottomRight);

	Serial.println("---------------setup completed---------------");

	mqttConnection.publish("/start");
}

void loop()
{
	tempreratureSensor.tick();
	hapticFeedback.update();
	buttonTopLeft.tick();
	buttonTopRight.tick();
	buttonBottomLeft.tick();
	buttonBottomRight.tick();
	mqttConnection.tick();

	delay(10);
}
