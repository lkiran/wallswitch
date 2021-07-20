#include <Arduino.h>
#include <numeric>

class TempreratureSensor
{
private:
    const int RESOULUTION = 12;
    const int MAX_MV = 3300;
    const double VOLT_TEMP_RATIO = 0.1;

    int _pin;
    double _volt;
    double _temp;
    unsigned long updatedOn;
    bool isAttached;

    std::vector<double> measurementHistory;

public:
    TempreratureSensor(int pin)
    {
        this->_pin = pin;
        analogSetPinAttenuation(this->_pin, adc_attenuation_t::ADC_0db);
        analogSetWidth(RESOULUTION);
        analogSetClockDiv(1);

        this->isAttached = adcAttachPin(this->_pin);
    }

    void tick()
    {
        if (this->isAttached == false)
            return;

        unsigned long now = millis();
        if (now - updatedOn < 1000)
            return;

        updatedOn = now;
        readMeasurement(1);
        calculateTemperature();

        Serial.print("Read ");
        Serial.print(this->_temp);
        Serial.println("°C");;
    }

    double tempCelcius()
    {
        return this->_temp;
    }

    void readMeasurement(int sampleSize)
    {
        this->measurementHistory.push_back(analogReadMilliVolts(this->_pin));
        if (this->measurementHistory.size() > sampleSize)
            this->measurementHistory.erase(this->measurementHistory.begin());
       
        double mVsum = std::accumulate(this->measurementHistory.begin(), this->measurementHistory.end(),
                                       decltype(this->measurementHistory)::value_type(0));

        this->_volt = mVsum / this->measurementHistory.size();
    }

    void calculateTemperature()
    {
        this->_temp = this->_volt * VOLT_TEMP_RATIO;
    }
};