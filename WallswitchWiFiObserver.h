#include "Observable.h"
#include "WiFiConnection.h"
#include "RgbLed.h"

class WallswitchWiFiObserver : public Observer
{
private:
    WiFiConnection &_wiFiConnection;
    RgbLed &_led;

public:
    explicit WallswitchWiFiObserver(WiFiConnection &wiFiConnection, RgbLed &led);
    ~WallswitchWiFiObserver();

    virtual void Update(Subject &theChangedSubject);
};

WallswitchWiFiObserver::WallswitchWiFiObserver(WiFiConnection &wiFiConnection, RgbLed &led)
    : _wiFiConnection(wiFiConnection), _led(led)
{
    _wiFiConnection.Attach(*this);
}

WallswitchWiFiObserver::~WallswitchWiFiObserver()
{
    _wiFiConnection.Detach(*this);
}

void WallswitchWiFiObserver::Update(Subject &subject)
{
    if (&subject == &_wiFiConnection)
    {
        if (_wiFiConnection.getStatus() == WL_CONNECTED)
        {
            Serial.println();
            Serial.println("WiFi connected");
            Serial.print("IP address: ");
            Serial.println(_wiFiConnection.getIP());
            this->_led.setColor(RGB::black);
        }
        else if (_wiFiConnection.getStatus() == WL_IDLE_STATUS)
        {
            Serial.print(".");
        }
        else if (_wiFiConnection.getStatus() == WL_IDLE_STATUS)
        {
            Serial.print(".");
        }
        else if (_wiFiConnection.getStatus() != WL_CONNECTED)
        {
            Serial.print("Connecting to ");
            Serial.println(_wiFiConnection.getSSID());
            this->_led.setColor(RGB::green);
        }
    }
}
