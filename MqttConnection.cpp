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
	Serial.print("MAC Address: ");
	Serial.println(Board::getMacAddress());

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
		this->connect();

	this->client.loop();
}

boolean MqttConnection::publish(String &topic)
{
	return publish(topic, "");
}

boolean MqttConnection::publish(String topic)
{
	String t = String(topic);
	return this->publish(t, emptyString);
}

boolean MqttConnection::publish(String &topic, String payload)
{
	String t = WiFi.macAddress() + topic;
	boolean result = this->client.publish(t, payload);
	if (result)
	{
		Serial.print("published ");
		Serial.print(topic);
		Serial.print(" ");
		Serial.println(payload);
	}
	else
	{
		Serial.print("publishing failed for ");
		Serial.print(topic);
		Serial.print(" ");
		Serial.println(payload);
	}

	return result;
}

void MqttConnection::subscribe(const String &topic, MqttCallback *handler)
{
	static String mac = WiFi.macAddress();
	String t = mac + String(topic);
	t.setKeep(true);
	this->client.subscribe(t, handler);
	Serial.print("now subscribing: ");
	Serial.println(t);
}

void MqttConnection::subscriptions()
{
	for (auto it = this->client.callbacks.begin(); it != this->client.callbacks.end(); ++it)
	{
		Serial.println(it->first);
	}
}
