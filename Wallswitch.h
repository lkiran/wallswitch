#include "OneButton.h"
#include "HapticFeedback.h"
#include "RgbLed.h"
#include "MqttConnection.h"

class Wallswitch : public OneButton
{
private:
    HapticFeedback *haptic;
    RgbLed *led;
    String title;

    virtual void handlePress(void);
    virtual void handleClick(void);
    virtual void handleDoubleClick(void);
    virtual void handleLongPressStart(void);
    // virtual void handleDuringLongPress(void);
    virtual void handleLongPressStop(void);

public:
    Wallswitch(int pin, int activeLow, bool pullupActive = true);
    Wallswitch(String title, int pin, int activeLow, bool pullupActive = true);
    void setHaptic(HapticFeedback *haptic);
    void setLed(RgbLed *led);
};
