#include <esp_log.h>
#include "Temperature.hpp"
#include "../../managed_components/espressif__onewire_bus/include/onewire_bus_impl_rmt.h"
#include "onewire_device.h"
#include "ds18b20.h"
#include "esp_timer.h"
#include "MqttClient.hpp"

static const char *TAG = "TEMPERATURE";
ds18b20_device_handle_t Temperature::handle = nullptr;
float Temperature::temperature = 0;

Temperature::Temperature(gpio_num_t pin) {
    // install 1-wire bus
    onewire_bus_handle_t bus = nullptr;
    onewire_bus_config_t bus_config = {
            .bus_gpio_num = pin,
    };
    onewire_bus_rmt_config_t rmt_config = {
            .max_rx_bytes = 10, // 1byte ROM command + 8byte ROM number + 1byte device command
    };
    ESP_ERROR_CHECK(onewire_new_bus_rmt(&bus_config, &rmt_config, &bus));

    onewire_device_iter_handle_t iter = nullptr;
    onewire_device_t next_onewire_device;
    esp_err_t search_result = ESP_OK;

    // create 1-wire device iterator, which is used for device search
    ESP_ERROR_CHECK(onewire_new_device_iter(bus, &iter));
    ESP_LOGI(TAG, "Device iterator created, start searching...");
    do {
        search_result = onewire_device_iter_get_next(iter, &next_onewire_device);
        if (search_result == ESP_OK) { // found a new device, let's check if we can upgrade it to a DS18B20
            ds18b20_config_t ds_cfg = {};
            // check if the device is a DS18B20, if so, return the ds18b20 handle
            if (ds18b20_new_device(&next_onewire_device, &ds_cfg, &handle) == ESP_OK) {
                ESP_LOGI(TAG, "Found a DS18B20 with address: %016llX", next_onewire_device.address);
            } else {
                ESP_LOGI(TAG, "Found an unknown device, address: %016llX", next_onewire_device.address);
            }
        }
    } while (search_result != ESP_ERR_NOT_FOUND);
    ESP_ERROR_CHECK(onewire_del_device_iter(iter));
    ESP_LOGI(TAG, "Searching done, DS18B20 device is found");
}

void Temperature::read(void *arg) {
    ESP_LOGI(TAG, "Reading temperature from DS18B20...");
    float read = 0;
    int64_t start_time = esp_timer_get_time();
    ESP_ERROR_CHECK(ds18b20_trigger_temperature_conversion(handle));
    ESP_ERROR_CHECK(ds18b20_get_temperature(handle, &read));
    ESP_LOGI(TAG, "Temperature read from DS18B20: %.2f°C in %lld ms", read,
             (esp_timer_get_time() - start_time) / 1000);
    // Check if temperature has changed by at least 0.01°C
    if (static_cast<int>(temperature * 100) != static_cast<int>(read * 100)) {
        MqttClient::publish("/temperature", to_string(read));
    }
    temperature = read;
}

esp_err_t Temperature::start() {
    const esp_timer_create_args_t timer_args = {
            .callback = Temperature::read,
            .arg = nullptr,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "temperature_timer",
            .skip_unhandled_events = true
    };
    esp_timer_handle_t timer;
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer));
    // Start the timer with a 5-second period
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer, 5000000));
    return ESP_OK;
}
