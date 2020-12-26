#ifndef MqttConnection_h
#define MqttConnection_h

#include "Board.h"
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

    boolean publish(String topic);
    boolean publish(String &topic);
    boolean publish(String &topic, String payload);
    void subscribe(const String &topic, MqttCallback *handler);
    void subscriptions();
    void tick();
};

#endif