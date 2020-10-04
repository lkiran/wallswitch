
#ifndef WiFiConnection_h
#define WiFiConnection_h

#include <WiFi.h>
#include "Observable.h"

class WiFiConnection : public Subject
{
public:
    static WiFiConnection &instance();

    WiFiConnection(WiFiConnection const &) = delete; // Don't forget to disable copy
    void operator=(WiFiConnection const &) = delete; // Don't forget to disable copy

    WiFiClient client;

    void connect(String ssid, String password);
    wl_status_t getStatus();
    IPAddress getIP();
    String getSSID();

private:
    WiFiConnection();  // forbid create instance outside
    ~WiFiConnection(); // forbid to delete instance outside

    String ssid;
    String password;
};

#endif