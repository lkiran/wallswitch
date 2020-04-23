#include <Arduino.h>

class TempreratureSensor
{
private:
    int _pin;
    int _raw;

public:
    TempreratureSensor(int pin)
    {
        this->_pin = pin;
        Serial.println("TempreratureSensor");
    }

    void update()
    {
        this->_raw = analogRead(this->_pin);
    }
    
    float tempCelcius()
    {
        return float(this->_raw);
    }
};