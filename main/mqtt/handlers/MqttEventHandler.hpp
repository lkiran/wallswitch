#pragma once

#include <string>
#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_system.h"
#include "esp_mac.h"

using namespace std;

class MqttEventHandler {
public:
    static void handle(void *args, esp_event_base_t base, int32_t event_id, void *event_data);

private:
    static void log_error_if_nonzero(const char *message, int error_code);
};