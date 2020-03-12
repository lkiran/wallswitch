#include <Arduino.h>
#include <vector>

#ifndef HapticFeedback_h
#define HapticFeedback_h

enum InstructionTypes
{
  off = 0,
  on = 1,
  idle
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
  std::vector<Instruction> instructionQueue;
  Instruction activeInstruction = Instruction{idle};
  unsigned long activatedAt;
  void setOutput(bool);

public:
  HapticFeedback();
  HapticFeedback(int pin);

  void update();
  void poke();
};

#endif