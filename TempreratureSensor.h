#include <Arduino.h>
#include <numeric>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "MqttConnection.h"

class TempreratureSensor
{
private:
    int _pin;
    float _temp;
    unsigned long updatedOn;
    String _topic;

    std::vector<float> measurementHistory;
    OneWire oneWire;
    DallasTemperature sensors;

    void readMeasurement(int sampleSize)
    {
        sensors.requestTemperatures();
        float temperatureC = sensors.getTempCByIndex(0);
        this->measurementHistory.push_back(temperatureC);
        if (this->measurementHistory.size() > sampleSize)
            this->measurementHistory.erase(this->measurementHistory.begin());

        float tempSum = std::accumulate(this->measurementHistory.begin(), this->measurementHistory.end(),
                                        decltype(this->measurementHistory)::value_type(0));

        this->_temp = tempSum / this->measurementHistory.size();

        Serial.print("Read ");
        Serial.print(temperatureC);
        Serial.print("°C, Ø ");
        Serial.print(this->_temp);
        Serial.print("°C of ");
        Serial.print(this->measurementHistory.size());
        Serial.println("");
    }

public:
    TempreratureSensor(int pin)
    {
        this->_pin = pin;
        this->_topic = String("/temperature");
        this->_topic.keep = true;
        oneWire = OneWire(pin);
        sensors = DallasTemperature(&oneWire);
        sensors.begin();
    }

    void tick()
    {
        unsigned long now = millis();
        if (now - updatedOn < 1000)
            return;
        updatedOn = now;

        readMeasurement(60);

        MqttConnection &mqttConnection = MqttConnection::instance();
        mqttConnection.publish(this->_topic, this->_temp);
    }

    float tempCelcius()
    {
        return this->_temp;
    }
};