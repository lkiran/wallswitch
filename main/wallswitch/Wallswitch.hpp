#pragma once

#include <cstdio>
#include <string>
#include <vector>
#include "esp_log.h"
#include "iot_button.h"

using namespace std;

/*
 * https://components.espressif.com/components/espressif/button
 */
extern "C"
class Wallswitch {
private:
    string title;
    gpio_num_t gpioNum;
    static vector<string> titles;
public:
    Wallswitch(const string &title, gpio_num_t pin);

    static void pressHandler(void *arg, void *usr_data);

    static void clickHandler(void *arg, void *usr_data);

    static void doubleClickHandler(void *arg, void *usr_data);

    static void longPressHandler(void *arg, void *usr_data);

};