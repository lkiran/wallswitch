#include "WiFiConnection.h"

// Constructor & Dectructor
WiFiConnection::WiFiConnection()
{
}

WiFiConnection::~WiFiConnection()
{
}

// methods

WiFiConnection &WiFiConnection::instance()
{
    // create instance by lazy initialization
    // guaranteed to be destroyed
    static WiFiConnection instance;

    return instance;
}

wl_status_t WiFiConnection::getStatus()
{
    return WiFi.status();
}

String WiFiConnection::getSSID()
{
    return this->ssid;
}

IPAddress WiFiConnection::getIP()
{
    return WiFi.localIP();
}

void WiFiConnection::connect(char *ssid, char *password)
{
    Notify();
    WiFi.begin(ssid, password);
    while (this->getStatus() != WL_CONNECTED)
    {
        delay(1000);
        Notify();
    }
    Notify();
}
