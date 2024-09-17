#pragma once

#include <string>
#include <cstddef>
#include "esp_log.h"
#include "mqtt_client.h"
#include "handlers/MqttEventHandler.hpp"


class MqttClient {
public:

    static esp_mqtt_client_handle_t client;

    static esp_err_t start();

    static string subscribe(const string &topic);

    static esp_err_t publish(const string &topic);

    static esp_err_t publish(const string &topic, const string &payload);
};