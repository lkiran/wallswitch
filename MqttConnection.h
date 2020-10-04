
#ifndef MqttConnection_h
#define MqttConnection_h

#include <ESP.h>
#include "WiFiConnection.h"
#include "PubSubClient.h"

class MqttConnection
{
private:
    PubSubClient client;
    String serverAddress;
    int mqttPort;

    MqttConnection();
    ~MqttConnection();

public:
    static MqttConnection &instance();

    MqttConnection(MqttConnection const &) = delete; // Don't forget to disable copy
    void operator=(MqttConnection const &) = delete; // Don't forget to disable copy

    String getServerAddress();
    int getMqttPort();

    void configure(String serverAddress, int port = 1883);
    void connect();

    void subscribe(String topic, MqttCallback &handler);
};

#endif