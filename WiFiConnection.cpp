#include "WiFiConnection.h"

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

void WiFiConnection::connect(String ssid, String password)
{
    this->ssid = ssid;
    this->password = password;
    Notify();
    char c_ssid[ssid.length()];
    strcpy(c_ssid, ssid.c_str());
    char c_password[password.length()];
    strcpy(c_password, password.c_str());
    WiFi.begin(c_ssid, c_password);
    while (this->getStatus() != WL_CONNECTED)
    {
        delay(1000);
        Notify();
    }
    Notify();
}
