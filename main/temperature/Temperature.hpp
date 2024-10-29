#pragma once

#include "driver/gpio.h"
#include "ds18b20.h"

extern "C"
class Temperature {
public:
    static float temperature;
    static ds18b20_device_handle_t handle;

    explicit Temperature(gpio_num_t pin);

    static void read(void *arg);

    static esp_err_t start();
};