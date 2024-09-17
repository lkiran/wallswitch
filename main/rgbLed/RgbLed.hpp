#pragma once

#include <string>
#include <map>
#include <vector>
#include "esp_log.h"
#include "led_indicator.h"

using namespace std;

/*
 * https://components.espressif.com/components/espressif/led_indicator
 */
extern "C"
class RgbLed {
private:
    string title;
    led_indicator_handle_t handle;
    static map<string, RgbLed> instances;

public:
    RgbLed(const string &title, gpio_num_t redPin, gpio_num_t greenPin, gpio_num_t bluePin);

    void setRgb(string& color);
    string getTitle();

    static RgbLed *getInstance(const string &topic);
    static void subscribeAll();
};
