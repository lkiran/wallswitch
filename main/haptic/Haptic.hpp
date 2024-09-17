#pragma once

#include <string>
#include <map>
#include <vector>
#include "esp_log.h"
#include "led_indicator.h"

#include "driver/gpio.h"
#include "led_indicator.h"

extern "C"
class Haptic {
public:
    explicit Haptic(gpio_num_t pin);

    static void poke();

private:
    static led_indicator_handle_t handle;
};
