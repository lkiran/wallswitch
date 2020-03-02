#include <Arduino.h>

#ifndef HapticFeedback_h
#define HapticFeedback_h

class HapticFeedback
{
private:
  int _pin;

public:
  HapticFeedback();
  HapticFeedback(int pin);

  void update();
  void poke();
};

#endif