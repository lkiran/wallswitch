#include <cmath>
#include "CustomRGBDriver.hpp"
#include "driver/ledc.h"
#include "esp_log.h"

static const char *TAG = "CustomRGBDriver";

#define LED_RGB_CHECK(a, str, action, ...)                    \
if (unlikely(!(a)))                                           \
{                                                             \
    ESP_LOGE(TAG, "%s(%d): %s", __FUNCTION__, __LINE__, str); \
    action;                                                   \
}

std::vector<ledc_channel_config_t> CustomRGBDriver::channels;

void channelConfig(custom_led_rgb_t *rgb, rgb_color_t color) {
    uint8_t channel = CustomRGBDriver::channels.size();
    ESP_LOGI(TAG, "channelConfig() s=%d", CustomRGBDriver::channels.size());

    rgb->speed[color] = (ledc_mode_t) (channel / 8);
    ledc_timer_t timer = (ledc_timer_t) ((channel / 2) % 4);

    ledc_timer_config_t ledc_timer = {
            .speed_mode       = rgb->speed[color],
            .duty_resolution  = LEDC_TIMER_8_BIT,
            .timer_num        = timer,
            .freq_hz          = 5000,
            .clk_cfg          = LEDC_AUTO_CLK,
            .deconfigure      = false
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    rgb->channel[color] = (ledc_channel_t) (channel % 8);

    ledc_channel_config_t ledc_channel = {
            .gpio_num       = rgb->gpio[color],
            .speed_mode     = rgb->speed[color],
            .channel        = rgb->channel[color],
            .intr_type      = LEDC_INTR_DISABLE,
            .timer_sel      = timer,
            .duty           = 0,
            .hpoint         = 0,
            .flags={
                    .output_invert = 1
            }
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    CustomRGBDriver::channels.push_back(ledc_channel);
    ESP_LOGI(TAG, "channelConfig() gpio=%d\ttimer=%d\tch=%d\tspeed=%d\tdone",
             rgb->gpio[color], timer, rgb->channel[color], rgb->speed[color]);
}

esp_err_t CustomRGBDriver::init(void *hardware_data) {
    ESP_LOGI(TAG, "init()");
    custom_led_rgb_t *rgb = (custom_led_rgb_t *) hardware_data;
    LED_RGB_CHECK(nullptr != rgb, "param pointer invalid", return ESP_ERR_INVALID_ARG);
    rgb->max_duty = (uint32_t) pow(2, LEDC_TIMER_8_BIT) - 1;
    channelConfig(rgb, RED);
    channelConfig(rgb, GREEN);
    channelConfig(rgb, BLUE);
    ESP_LOGI(TAG, "init()\tdone");
    return ESP_OK;
}

esp_err_t CustomRGBDriver::deinit(void *hardware_data) {
    LED_RGB_CHECK(nullptr != hardware_data, "rgb_handle pointer invalid",
                  return ESP_ERR_INVALID_ARG);
    return ESP_OK;
}

static esp_err_t setDuty(custom_led_rgb_t *p_rgb, uint32_t rgb[]) {
    esp_err_t ret;
    if (!p_rgb->is_active_level_high) {
        rgb[0] = p_rgb->max_duty - rgb[0];
        rgb[1] = p_rgb->max_duty - rgb[1];
        rgb[2] = p_rgb->max_duty - rgb[2];
    }
    for (int i = 0; i < 3; i++) {
        ret = ledc_set_duty(p_rgb->speed[i], p_rgb->channel[i], rgb[i]);
        LED_RGB_CHECK(ESP_OK == ret, "LEDC set duty error", return ret);
        ret = ledc_update_duty(p_rgb->speed[i], p_rgb->channel[i]);
        LED_RGB_CHECK(ESP_OK == ret, "LEDC update duty error", return ret);
    }
    return ESP_OK;
}

esp_err_t CustomRGBDriver::setOnOff(void *hardware_data, bool on_off) {
    esp_err_t ret;
    LED_RGB_CHECK(NULL != hardware_data, "rgb_handle pointer invalid",
                  return ESP_ERR_INVALID_ARG);
    custom_led_rgb_t *p_rgb = (custom_led_rgb_t *) hardware_data;

    if (on_off) {
        uint32_t rgb[3] = {0};
        led_indicator_hsv2rgb(p_rgb->hsv.value, &rgb[0], &rgb[1], &rgb[2]);
        ret = setDuty(p_rgb, rgb);
        LED_RGB_CHECK(ESP_OK == ret, "LEDC set duty error", return ret);
    } else {
        uint32_t rgb[3] = {0, 0, 0};
        ret = setDuty(p_rgb, rgb);
        LED_RGB_CHECK(ESP_OK == ret, "LEDC set duty error", return ret);
    }

    return ESP_OK;
}

esp_err_t CustomRGBDriver::setRGB(void *hardware, uint32_t rgb_value) {
    esp_err_t ret;
    custom_led_rgb_t *p_rgb = (custom_led_rgb_t *) hardware;
    uint32_t rgb[3];
    rgb[0] = GET_RED(rgb_value) * p_rgb->max_duty / UINT8_MAX;
    rgb[1] = GET_GREEN(rgb_value) * p_rgb->max_duty / UINT8_MAX;
    rgb[2] = GET_BLUE(rgb_value) * p_rgb->max_duty / UINT8_MAX;

    ret = setDuty(p_rgb, rgb);
    LED_RGB_CHECK(ESP_OK == ret, "LEDC set duty error", return ret);
    p_rgb->hsv.value = led_indicator_rgb2hsv(rgb_value);
    return ESP_OK;
}

esp_err_t CustomRGBDriver::setHSV(void *hardware, uint32_t hsv_value) {
    ESP_LOGI(TAG, "setHSV()");
    esp_err_t ret;
    custom_led_rgb_t *p_rgb = (custom_led_rgb_t *) hardware;
    uint32_t rgb[3];
    led_indicator_hsv2rgb(hsv_value, &rgb[0], &rgb[1], &rgb[2]);
    for (int i = 0; i < 3; i++) {
        rgb[i] = rgb[i] * p_rgb->max_duty / UINT8_MAX;
    }

    ret = setDuty(p_rgb, rgb);
    LED_RGB_CHECK(ESP_OK == ret, "LEDC set duty error", return ret);
    p_rgb->hsv.value = hsv_value;
    ESP_LOGI(TAG, "setHSV()\tdone");
    return ESP_OK;
}

esp_err_t CustomRGBDriver::setBrightness(void *hardware_data, uint32_t brightness) {
    esp_err_t ret;
    custom_led_rgb_t *p_rgb = (custom_led_rgb_t *) hardware_data;
    uint32_t rgb[3];
    p_rgb->hsv.v = brightness;
    led_indicator_hsv2rgb(p_rgb->hsv.value, &rgb[0], &rgb[1], &rgb[2]);
    for (int i = 0; i < 3; i++) {
        rgb[i] = rgb[i] * p_rgb->max_duty / UINT8_MAX;
    }

    ret = setDuty(p_rgb, rgb);
    LED_RGB_CHECK(ESP_OK == ret, "LEDC set duty error", return ret);
    return ESP_OK;
}