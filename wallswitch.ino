#include "Wallswitch.h"
#include "WallswitchWiFiObserver.h"
#include "HapticFeedback.h"
#include "RgbLed.h"
#include "TempreratureSensor.h"
#include "WiFiConnection.h"
#include "MqttConnection.h"

// TempreratureSensor tempreratureSensor(26);
HapticFeedback hapticFeedback(23);

RgbLed rgbLedTopLeft(18, 5, 17);
RgbLed rgbLedTopRight(25, 33, 32);
RgbLed rgbLedBottomLeft(4, 16, 2);
RgbLed rgbLedBottomRight(12, 14, 27);

Wallswitch buttonTopLeft(19, false);
Wallswitch buttonTopRight(35, false);
Wallswitch buttonBottomLeft(15, false);
Wallswitch buttonBottomRight(13, false);

WiFiConnection &wifiConnection = WiFiConnection::instance();
MqttConnection &mqttConnection = MqttConnection::instance();

void setup()
{
  Serial.begin(115200);
  Serial.println("---------------starting setup---------------");

  buttonTopLeft.setHaptic(&hapticFeedback);
  buttonTopRight.setHaptic(&hapticFeedback);
  buttonBottomLeft.setHaptic(&hapticFeedback);
  buttonBottomRight.setHaptic(&hapticFeedback);

  buttonTopLeft.setLed(&rgbLedTopLeft);
  buttonTopRight.setLed(&rgbLedTopRight);
  buttonBottomLeft.setLed(&rgbLedBottomLeft);
  buttonBottomRight.setLed(&rgbLedBottomRight);

  rgbLedTopLeft.setColor(RGB::white);
  rgbLedTopRight.setColor(RGB::white);
  rgbLedBottomLeft.setColor(RGB::white);
  rgbLedBottomRight.setColor(RGB::white);

  WallswitchWiFiObserver(wifiConnection, rgbLedTopLeft);
  wifiConnection.connect("ALTINTAS2", "AB12CD34");

  mqttConnection.configure((char *)"10.0.0.51");
  mqttConnection.connect();

  mqttConnection.subscriptions();

  Serial.println("---------------setup completed---------------");
}

void loop()
{
  // tempreratureSensor.update();
  hapticFeedback.update();
  buttonTopLeft.tick();
  buttonTopRight.tick();
  buttonBottomLeft.tick();
  buttonBottomRight.tick();
  mqttConnection.tick();

  delay(10);
}
