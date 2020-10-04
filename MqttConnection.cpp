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

void MqttConnection::configure(char *serverAddress, int port)
{
  this->serverAddress = serverAddress;
  this->mqttPort = port;
  WiFiConnection &wifiConnection = WiFiConnection::instance();
  PubSubClient pubSubclient(wifiConnection.client);
  pubSubclient.setServer(this->serverAddress, this->mqttPort);
  this->client = pubSubclient;
}

String mac2String(byte ar[])
{
  String s;
  for (byte i = 0; i < 6; ++i)
  {
    char buf[3];
    sprintf(buf, "%02X", ar[i]); // J-M-L: slight modification, added the 0 in the format for padding
    s += buf;
    if (i < 5)
      s += ':';
  }
  return s;
}

void MqttConnection::connect()
{
  /* Loop until reconnected */
  while (!this->client.connected())
  {
    unsigned long long chipid = ESP.getEfuseMac();
    String mac = mac2String((byte *)&chipid);
    Serial.print("MAC Address: ");
    Serial.println(mac);

    Serial.print("MQTT connecting to: ");
    Serial.println(this->serverAddress);
    /* client ID */
    String clientId = mac;
    /* connect now */
    if (this->client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      MqttCallback ledCallback;
      client.subscribe("/led/top-left", ledCallback);
      client.subscribe("smarthome/room1/led", ledCallback);
      /* subscribe topics HERE*/
    }
    else
    {
      Serial.print("failed, status code ");
      Serial.println(this->client.state());
      Serial.println("try again in 5 seconds");
      /* Wait 5 seconds before retrying */
      delay(5000);
    }
  }
}

void MqttConnection::tick(){
  this->client.loop();
}

void MqttConnection::subscribe(String topic, MqttCallback &handler)
{
  this->client.subscribe(topic, handler);
}

void MqttConnection::subscriptions()
{
  for (auto it = this->client.callbacks.begin(); it != this->client.callbacks.end(); ++it)
  {
    if (it == this->client.callbacks.end())
      Serial.println("it == this->client.callbacks.end()");
    else
      Serial.print("it->first: ");
    Serial.println(it->first);
  }
}