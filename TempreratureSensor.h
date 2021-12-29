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
    DeviceAddress address;

    void readMeasurement(int sampleSize)
    {
        unsigned long now = millis();
        sensors.requestTemperatures();
        float temperatureC = sensors.getTempCByIndex(0);
    
        if (temperatureC == -127.00)
        {
            Serial.println("Can't read from DS18B20 temperature sensor");
            return;
        }

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
        Serial.println(this->measurementHistory.size());
    }

public:
    TempreratureSensor(int pin): _pin(pin), _topic("/temperature")
    {
        oneWire = OneWire(pin);
        sensors = DallasTemperature(&oneWire);
        sensors.begin();
        bool sensorFound = sensors.getAddress(address, 0);
        // if (sensorFound)
        // {
        //     sensors.setResolution(address, 9);
        // }
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