
#include <ESP.h>
#include "WiFiConnection.h"
#include "PubSubClient.h"

#ifndef MqttConnection_h
#define MqttConnection_h

class MqttConnection
{
private:
    PubSubClient client;
    char *serverAddress;
    int mqttPort;

    MqttConnection();
    ~MqttConnection();
    static void receivedCallback(char *topic, byte *payload, unsigned int length);

public:
    static MqttConnection &instance();

    MqttConnection(MqttConnection const &) = delete; // Don't forget to disable copy
    void operator=(MqttConnection const &) = delete; // Don't forget to disable copy

    char *getServerAddress();
    int getMqttPort();

    void configure(char *serverAddress, int port = 1883);
    void connect();
};

#endif