#include "Observable.h"
#include "WiFiConnection.h"
#include "RgbLed.h"

class WallswitchWiFiObserver : public Observer
{
private:
    /* data */
public:
    WallswitchWiFiObserver(WiFiConnection *wiFiConnection, RgbLed *led);
    ~WallswitchWiFiObserver();

    virtual void Update(Subject& theChangedSubject);
};

WallswitchWiFiObserver::WallswitchWiFiObserver(WiFiConnection *wiFiConnection, RgbLed *led)
{
}

WallswitchWiFiObserver::~WallswitchWiFiObserver()
{
}

void WallswitchWiFiObserver::Update(Subject& subject) 
{

}
