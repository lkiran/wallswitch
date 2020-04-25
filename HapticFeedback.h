#include <Arduino.h>
#include <vector>

#ifndef HapticFeedback_h
#define HapticFeedback_h

enum InstructionTypes
{
  off = 0,
  on = 1,
  idle = 2,
};

class HapticFeedback
{
private:
  struct Instruction
  {
    InstructionTypes instructionType;
    unsigned long int duration;
  };

  int pin;
  std::vector<HapticFeedback::Instruction> instructionQueue;
  Instruction activeInstruction = HapticFeedback::Instruction{idle};
  unsigned long activatedAt;
  void setOutput(bool);

public:
  HapticFeedback();
  HapticFeedback(int pin);

  void update();
  void poke();
};

#endif