#include "OneButton.h"
#include "HapticFeedback.h"
#include "RgbLed.h"

class Wallswitch : public OneButton
{
private:
    HapticFeedback haptic;
    RgbLed led;

    virtual void handleClick(void);
    virtual void handleDoubleClick(void);
    virtual void handleLongPressStart(void);

public:
    Wallswitch(int pin, int activeLow, bool pullupActive = true);
    void setHaptic(HapticFeedback haptic);
    void setLed(RgbLed led);
};
