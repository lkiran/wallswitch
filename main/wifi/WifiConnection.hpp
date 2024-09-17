#pragma once

#include "esp_err.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "sdkconfig.h"

extern "C" class WifiConnection {
public:
    static void start();

    static void stop();

    static void shutdown_handler();

    static esp_err_t connect();
private:
};