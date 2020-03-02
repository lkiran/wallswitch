#include "OneButton.h"
#include "HapticFeedback.h"

class Wallswitch : public OneButton
{
private:
    HapticFeedback haptic;
    virtual void handleClick(void);
    virtual void handleDoubleClick(void);
    virtual void handleLongPressStart(void);

public:
    Wallswitch(int pin, int activeLow, bool pullupActive = true);
    void setHaptic(HapticFeedback haptic);
};
