
#include "Board.h"
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

    MqttConnection() = default;
    ~MqttConnection() = default;
    MqttConnection(const MqttConnection &) = delete;
    MqttConnection &operator=(const MqttConnection &) = delete;

public:
    static MqttConnection &instance();
    char *getServerAddress();
    int getMqttPort();

    void configure(char *serverAddress, int port = 1883);
    void connect();

    void subscribe(String topic, MqttCallback &handler);
    void subscriptions();
    void tick();
};

#endif