#include "HapticFeedback.h"

HapticFeedback::HapticFeedback()
{
}

HapticFeedback::HapticFeedback(int pin)
{
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void HapticFeedback::setOutput(bool state)
{
  digitalWrite(pin, state);
}

void HapticFeedback::update()
{
  unsigned long now = millis();
  if (this->activeInstruction.instructionType == idle)
  {
    if (!this->instructionQueue.empty())
    {
      this->activeInstruction = this->instructionQueue.front();
      this->instructionQueue.erase(this->instructionQueue.begin());
      this->activatedAt = now;
      this->setOutput(this->activeInstruction.instructionType == on);
    }
  }
  else
  {
    if ((now - this->activatedAt) >= this->activeInstruction.duration)
    {
      this->activeInstruction.instructionType = idle;
      this->setOutput(LOW);
    }
  }
}

void HapticFeedback::poke()
{
  this->instructionQueue.push_back(HapticFeedback::Instruction{on, 300});
  this->instructionQueue.push_back(HapticFeedback::Instruction{off, 100});
}