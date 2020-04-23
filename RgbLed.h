#ifndef RgbLed_h
#define RgbLed_h
#include "RGB.h"


class RgbLed
{
private:
    byte redPin;
    byte greenPin;
    byte bluePin;
    RGB color;
    bool active = true;

    void driveLeds(RGB color)
    {
        if (this->redPin)
        {
            ledcWrite(1, color.getRed());
        }

        if (this->greenPin)
        {
            ledcWrite(2, color.getGreen());
        }

        if (this->bluePin)
        {
            ledcWrite(3, color.getBlue());
        }
    }

public:
    RgbLed()
    {
    }

    RgbLed(byte redPin, byte greenPin, byte bluePin)
    {
        this->redPin = redPin;
        this->greenPin = greenPin;
        this->bluePin = bluePin;

        if (this->redPin)
        {
            ledcAttachPin(redPin, 1); // assign led pin to channel
            ledcSetup(1, 12000, 8);   // 12 kHz PWM, 8-bit resolution
        }

        if (this->greenPin)
        {
            ledcAttachPin(greenPin, 2);
            ledcSetup(2, 12000, 8);
        }

        if (this->bluePin)
        {
            ledcAttachPin(bluePin, 3);
            ledcSetup(3, 12000, 8);
        }
         Serial.println("RgbLed");
    }

    void setColor(RGBA color)
    {
        this->setColor(color.toRGB());
    }

    void setColor(RGB color)
    {
        this->driveLeds(color);
        this->color = color;
    }

    void turnOn()
    {
        this->active = true;
        this->setColor(this->color);
    }

    void turnOff()
    {
        this->active = false;
        this->driveLeds(black);
    }

    RGB getColor(void)
    {
        return this->color;
    }
};

#endif