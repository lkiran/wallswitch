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

void WiFiConnection::connect(char *ssid, char *password)
{
    Serial.print("Connecting to ");
    Serial.println(ssid);

    Notify();
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Notify();
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
