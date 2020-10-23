#include <WiFi.h>
#include "Observable.h"

#ifndef WiFiConnection_h
#define WiFiConnection_h

class WiFiConnection : public Subject
{
private:
    String ssid;
    String password;

    WiFiConnection() = default;
    ~WiFiConnection() = default;
    WiFiConnection(const WiFiConnection &) = delete;
    WiFiConnection &operator=(const WiFiConnection &) = delete;

public:
    static WiFiConnection &instance();
    WiFiClient client;

    void connect(String ssid, String password);
    wl_status_t getStatus();
    IPAddress getIP();
    String getSSID();
};

#endif