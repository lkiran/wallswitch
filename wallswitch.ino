#include "HapticFeedback.h"
#include "LinkedList.h"
#include "Wallswitch.h"
#include "RgbLed.h"
#include "TempreratureSensor.h"

TempreratureSensor tempreratureSensor(16);
HapticFeedback hapticFeedback(17);

RgbLed rgbLedTopLeft;
RgbLed rgbLedTopRight;
RgbLed rgbLedBottomLeft;
RgbLed rgbLedBottomRight;

Wallswitch buttonTopLeft(12, true);
Wallswitch buttonTopRight(13, true);
Wallswitch buttonBottomLeft(14, true);
Wallswitch buttonBottomRight(15, true);

void setup()
{
  buttonBottomLeft.setHaptic(hapticFeedback);

  Serial.begin(921600);
  Serial.println("---------------Ready---------------");
  rgbLedBottomLeft.setColor(white);
}

void loop()
{
  tempreratureSensor.update();
  hapticFeedback.update();
  buttonTopLeft.tick();
  buttonTopRight.tick();
  buttonBottomLeft.tick();
  buttonBottomRight.tick();
}