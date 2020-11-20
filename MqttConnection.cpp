#include "MqttConnection.h"

MqttConnection &MqttConnection::instance()
{
	Serial.print("&MqttConnection::instance()");
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

void MqttConnection::connect()
{
	Serial.println("MAC Address: " + Board::getMacAddress());

	/* Loop until reconnected */
	while (!this->client.connected())
	{
		Serial.print("MQTT connecting to: ");
		Serial.println(this->serverAddress);

		/* connect now */
		if (this->client.connect(Board::getMacAddress().c_str()))
		{
			Serial.println("MQTT connected");
		}
		else
		{
			Serial.print("MQTT connection failed, status code ");
			Serial.println(this->client.state());
			Serial.println("try again in 5 seconds...");
			/* Wait 5 seconds before retrying */
			delay(5000);
		}
	}
}

void MqttConnection::tick()
{
	if (!this->client.connected())
		this->connect();

	this->client.loop();
}

void MqttConnection::subscribe(String topic, MqttCallback *handler)
{
	topic = WiFi.macAddress() + topic;
	this->client.subscribe(topic, handler);
	Serial.println("now subscribing: " + topic);
}

void MqttConnection::subscriptions()
{
	for (auto it = this->client.callbacks.begin(); it != this->client.callbacks.end(); ++it)
	{
		Serial.println(it->first);
	}
}
