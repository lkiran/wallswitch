#include "Wallswitch.hpp"
#include "MqttClient.hpp"
#include "Haptic.hpp"

static const char *TAG = "WALLSWITCH";
vector<string> Wallswitch::titles;

Wallswitch::Wallswitch(const string &title, gpio_num_t gpioNum) : title(title), gpioNum(gpioNum) {
    if (ranges::find(Wallswitch::titles.begin(), Wallswitch::titles.end(), title) == Wallswitch::titles.end()) {
        Wallswitch::titles.push_back(title);
    }

    button_config_t gpio_btn_cfg = {
            .type = BUTTON_TYPE_GPIO,
            .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
            .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
            .gpio_button_config = {
                    .gpio_num = gpioNum,
                    .active_level = 1,
            },
    };
    button_handle_t gpio_btn = iot_button_create(&gpio_btn_cfg);
    if (nullptr == gpio_btn) {
        ESP_LOGE(TAG, "Button create failed");
    }
    int titleIndex = distance(Wallswitch::titles.begin(),
                              ranges::find(Wallswitch::titles.begin(), Wallswitch::titles.end(), title));
    iot_button_register_cb(gpio_btn, BUTTON_SINGLE_CLICK, Wallswitch::clickHandler,
                           reinterpret_cast<void *>(titleIndex));
    iot_button_register_cb(gpio_btn, BUTTON_DOUBLE_CLICK, Wallswitch::doubleClickHandler,
                           reinterpret_cast<void *>(titleIndex));
    iot_button_register_cb(gpio_btn, BUTTON_LONG_PRESS_START, Wallswitch::longPressHandler,
                           reinterpret_cast<void *>(titleIndex));
    iot_button_register_cb(gpio_btn, BUTTON_PRESS_DOWN, Wallswitch::pressHandler,
                           reinterpret_cast<void *>(titleIndex));
    ESP_LOGI(TAG, "Button callbacks are registered for %s", title.c_str());
}

void Wallswitch::pressHandler(void *arg, void *usr_data) {
    int titleIndex = reinterpret_cast<int>(usr_data);
    auto title = Wallswitch::titles.at(titleIndex);
    ESP_LOGI(TAG, "Button (%s) is pressed", title.c_str());
    Haptic::poke();
}

void Wallswitch::clickHandler(void *arg, void *usr_data) {
    int titleIndex = reinterpret_cast<int>(usr_data);
    auto title = Wallswitch::titles.at(titleIndex);
    ESP_LOGI(TAG, "Button (%s) is clicked", title.c_str());
    MqttClient::publish("/button/" + title, "clicked");
}

void Wallswitch::doubleClickHandler(void *arg, void *usr_data) {
    int titleIndex = reinterpret_cast<int>(usr_data);
    auto title = Wallswitch::titles.at(titleIndex);
    ESP_LOGI(TAG, "Button (%s) is double clicked", title.c_str());
    MqttClient::publish("/button/" + title, "double-clicked");
}

void Wallswitch::longPressHandler(void *arg, void *usr_data) {
    int titleIndex = reinterpret_cast<int>(usr_data);
    auto title = Wallswitch::titles.at(titleIndex);
    ESP_LOGI(TAG, "Button (%s) is long pressed", title.c_str());
    MqttClient::publish("/button/" + title, "long-pressed");
    Haptic::poke();
}
