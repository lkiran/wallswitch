#include "HapticFeedback.h"
#include "LinkedList.h"
#include "Wallswitch.h"
#include "RgbLed.h"
#include "TempreratureSensor.h"

TempreratureSensor tempreratureSensor(25);
HapticFeedback hapticFeedback(33);

RgbLed rgbLedTopLeft(36, 39, 34);
RgbLed rgbLedTopRight(18, 5, 17);
RgbLed rgbLedBottomLeft(14, 12, 13);
RgbLed rgbLedBottomRight(4, 2, 15);

Wallswitch buttonTopLeft(35, true);
Wallswitch buttonTopRight(23, true);
Wallswitch buttonBottomLeft(27, true);
Wallswitch buttonBottomRight(16, true);

void setup()
{
  Serial.begin(921600);

  buttonTopLeft.setHaptic(hapticFeedback);
  buttonTopRight.setHaptic(hapticFeedback);
  buttonBottomLeft.setHaptic(hapticFeedback);
  buttonBottomRight.setHaptic(hapticFeedback);

  rgbLedTopLeft.setColor(white);
  rgbLedTopRight.setColor(white);
  rgbLedBottomLeft.setColor(white);
  rgbLedBottomRight.setColor(white);

  Serial.println("---------------Ready---------------");
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