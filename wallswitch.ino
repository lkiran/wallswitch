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

  WiFiConnection &wifiConnection = WiFiConnection::instance();
  WallswitchWiFiObserver(wifiConnection, rgbLedTopLeft);
  wifiConnection.connect("ALTINTAS2", "AB12CD34");

  MqttConnection &mqttConnection = MqttConnection::instance();
  mqttConnection.configure((char *)"10.0.0.51");
  mqttConnection.connect();

  MqttCallback LedCallback;
  mqttConnection.subscribe("/led/top-left", LedCallback);
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
  delay(10);
}
