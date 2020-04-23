#include "HapticFeedback.h"

HapticFeedback::HapticFeedback()
{
}

HapticFeedback::HapticFeedback(int pin)
{
  this->pin = pin;
  Serial.println("HapticFeedback");
}

void HapticFeedback::setOutput(bool state)
{
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
      this->setOutput(false);
    }
  }
}

void HapticFeedback::poke()
{
  this->instructionQueue.push_back(Instruction{on, 100});
}