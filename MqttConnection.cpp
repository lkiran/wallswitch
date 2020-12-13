#include "MqttConnection.h"

MqttConnection &MqttConnection::instance()
{
	static MqttConnection instance;
	return instance;
}

const char *MqttConnection::getServerAddress()
{
	return this->serverAddress;
}

int MqttConnection::getMqttPort()
{
	return this->mqttPort;
}

void MqttConnection::configure(const char *serverAddress, int port)
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
		if (this->client.connect(WiFi.macAddress().c_str()))
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
	{
		this->connect();
	}
	this->client.loop();
}

boolean MqttConnection::publish(const char *topic)
{
	return this->publish(topic, "");
}

boolean MqttConnection::publish(const char *topic, const char *payload)
{
	String t = WiFi.macAddress() + String(topic);
	boolean result = this->client.publish(t, payload);
	if (result == false)
		Serial.println("publishing failed for " + String(topic) + " " + payload);
	else
		Serial.println("published " + String(topic) + " " + payload);

	return result;
}

void MqttConnection::subscribe(const char *topic, MqttCallback *handler)
{
	String t = WiFi.macAddress() + String(topic);
	this->client.subscribe(t.c_str(), handler);
	Serial.println("now subscribing: " + String(topic));
}

void MqttConnection::subscriptions()
{
	for (auto it = this->client.callbacks.begin(); it != this->client.callbacks.end(); ++it)
	{
		Serial.println(it->first);
	}
}
