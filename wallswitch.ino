#include "HapticFeedback.h"
#include "LinkedList.h"
#include "Wallswitch.h"
#include "RgbLed.h"
#include "TempreratureSensor.h"

// TempreratureSensor tempreratureSensor(25);
HapticFeedback hapticFeedback(23);

// RgbLed rgbLedTopLeft(36, 34, 36);
// RgbLed rgbLedTopRight(18, 5, 17);
// RgbLed rgbLedBottomLeft(14, 12, 13);
// RgbLed rgbLedBottomRight(4, 2, 15);

Wallswitch buttonTopLeft(21, false);
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

  // rgbLedTopLeft.setColor(blue);
  // rgbLedTopRight.setColor(blue);
  // rgbLedBottomLeft.setColor(blue);
  // rgbLedBottomRight.setColor(blue);

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