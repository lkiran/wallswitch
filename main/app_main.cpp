#include <cstdio>
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "wallswitch/Wallswitch.hpp"
#include "MqttClient.hpp"
#include "WifiConnection.hpp"
#include "RgbLed.hpp"
#include "Haptic.hpp"
#include "Temperature.hpp"


static const char *TAG = "MAIN";

extern "C"
void app_main(void) {
    esp_log_level_set("*", ESP_LOG_NONE);
    esp_log_level_set("MAIN", ESP_LOG_INFO);
    esp_log_level_set("WIFI", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_INFO);
    esp_log_level_set("MQTT_HANDLER", ESP_LOG_INFO);
    esp_log_level_set("WALLSWITCH", ESP_LOG_INFO);
    esp_log_level_set("RGB_LED", ESP_LOG_INFO);
    esp_log_level_set("HAPTIC", ESP_LOG_INFO);
    esp_log_level_set("TEMPERATURE", ESP_LOG_ERROR);

    ESP_LOGI(TAG, "Startup..");
    ESP_LOGI(TAG, "Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "IDF version: %s", esp_get_idf_version());

    Temperature temperature(GPIO_NUM_26);
    Haptic haptic(GPIO_NUM_23);

    Wallswitch buttonTopLeft("top-left", GPIO_NUM_19);
    Wallswitch buttonTopRight("top-right", GPIO_NUM_35);
    Wallswitch buttonBottomLeft("bottom-left", GPIO_NUM_15);
    Wallswitch buttonBottomRight("bottom-right", GPIO_NUM_13);

    RgbLed ledTopLeft("top-left", GPIO_NUM_18, GPIO_NUM_5, GPIO_NUM_17);
    RgbLed ledTopRight("top-right", GPIO_NUM_25, GPIO_NUM_33, GPIO_NUM_32);
    RgbLed ledBottomLeft("bottom-left", GPIO_NUM_4, GPIO_NUM_16, GPIO_NUM_2);
    RgbLed ledBottomRight("bottom-right", GPIO_NUM_12, GPIO_NUM_14, GPIO_NUM_27);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(WifiConnection::connect());
    ESP_ERROR_CHECK(MqttClient::start());
    ESP_ERROR_CHECK(Temperature::start());
}

