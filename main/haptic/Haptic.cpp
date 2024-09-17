#include "Haptic.hpp"

static const char *TAG = "HAPTIC";

led_indicator_handle_t Haptic::handle = nullptr;
enum {
    POKE_ONCE = 0,
    PATTERN_MAX,
};

const blink_step_t poke_once[] = {
        {LED_BLINK_HOLD, LED_STATE_ON, 150}, // vibrate
        {LED_BLINK_HOLD, LED_STATE_OFF, 0}, // stop
        {LED_BLINK_STOP, 0,            0}, // end
};

blink_step_t const *vibrate_patterns[] = {
        [POKE_ONCE] = poke_once,
        [PATTERN_MAX] = nullptr,
};

Haptic::Haptic(gpio_num_t pin) {
    led_indicator_gpio_config_t gpio_config = {
            .is_active_level_high = true,
            .gpio_num = pin,
    };
    led_indicator_config_t config = {
            .mode = LED_GPIO_MODE,
            .led_indicator_gpio_config = &gpio_config,
            .blink_lists = vibrate_patterns,
            .blink_list_num = PATTERN_MAX,
    };
    handle = led_indicator_create(&config);
    if (handle == nullptr) {
        ESP_LOGE(TAG, "Failed to create vibrator handle");
    }
}

void Haptic::poke() {
    ESP_LOGI(TAG, "Poking once");
    ESP_ERROR_CHECK(led_indicator_start(handle, POKE_ONCE));
}