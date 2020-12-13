#ifndef MqttConnection_h
#define MqttConnection_h

#include "Board.h"
#include "WiFi.h"
#include "WiFiConnection.h"
#include "PubSubClient.h"

class MqttConnection
{
private:
    PubSubClient client;
    const char *serverAddress;
    int mqttPort;

    MqttConnection() = default;
    ~MqttConnection() = default;
    MqttConnection(const MqttConnection &) = delete;
    MqttConnection &operator=(const MqttConnection &) = delete;

public:
    static MqttConnection &instance();
    const char *getServerAddress();
    int getMqttPort();

    void configure(const char *serverAddress, int port = 1883);
    void connect();

    boolean publish(const char *topic);
    boolean publish(const char *topic, const char *payload);
    void subscribe(const char *topic, MqttCallback *handler);
    void subscriptions();
    void tick();
};

#endif