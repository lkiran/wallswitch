#include "MqttConnection.h"

MqttConnection::MqttConnection()
{
}

MqttConnection::~MqttConnection()
{
}

MqttConnection &MqttConnection::instance()
{
    static MqttConnection instance;

    return instance;
}

char *MqttConnection::getServerAddress()
{
    return this->serverAddress;
}

int MqttConnection::getMqttPort()
{
    return this->mqttPort;
}


void MqttConnection::receivedCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received: ");
  Serial.println(topic);

  Serial.print("payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void MqttConnection::configure(char *serverAddress, int port)
{
    WiFiConnection &wifiConnection = WiFiConnection::instance();
    PubSubClient pubSubclient(wifiConnection.client);
    this->serverAddress = serverAddress;
    this->mqttPort = port;
    pubSubclient.setServer(this->serverAddress, this->mqttPort);
    pubSubclient.setCallback(MqttConnection::receivedCallback);
    this->client = &pubSubclient;
}

