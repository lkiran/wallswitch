#pragma once

#include <vector>
#include "driver/ledc.h"
#include "led_convert.h"

typedef enum {
    RED = 0,
    GREEN = 1,
    BLUE = 2,
} rgb_color_t;

typedef struct {
    bool is_active_level_high;        /*!< Set true if GPIO level is high when light is ON, otherwise false. */
    gpio_num_t gpio[3];
    ledc_channel_t channel[3];
    ledc_mode_t speed[3];
    uint32_t max_duty;             /*!< Max duty cycle from duty_resolution : 2^duty_resolution -1 */
    led_indicator_ihsv_t hsv;      /*!< HSV: H [0-360] - 9 bits, S [0-255] - 8 bits, V [0-255] - 8 bits*/
} custom_led_rgb_t;

extern "C"
class CustomRGBDriver {
private:

public:
    static std::vector<ledc_channel_config_t> channels;

/**
 * @brief Initialize the RGB LED indicator (WS2812 SK6812).
 *
 * @param param Pointer to initialization parameters.
 * @param ret_rgb Pointer to a variable that will hold the LED RGB instance.
 * @return esp_err_t
 *     - ESP_OK: Success
 *     - ESP_FAIL: Initialization failed
 *     - ESP_ERR_INVALID_ARG: Invalid argument provided
 *     - ESP_ERR_NO_MEM: Memory allocation failed
 */
    static esp_err_t init(void *hardware_data);

/**
 * @brief Deinitialize led RGB which is used by the LED indicator.
 *
 * @param hardware_data LED indicator LED RGB operation handle
 * @return esp_err_t
 *     - ESP_OK Success
 *     - ESP_FAIL Deinit fail
 */
    static esp_err_t deinit(void *hardware_data);

/**
 * @brief Turn the LED indicator on or off.
 *
 * @param hardware_data LED indicator LED RGB operation handle.
 * @param on_off Set to 0 or 1 to control the LED (0 for off, 1 for on).
 * @return esp_err_t
 *     - ESP_OK: Success
 *     - ESP_ERR_INVALID_ARG: Invalid argument provided
 *     - ESP_FAIL: LEDC channel initialization failed
 */
    static esp_err_t setOnOff(void *hardware_data, bool on_off);

/**
 * @brief Set the RGB color for the LED indicator.
 *
 * @param hardware  LED indicator LED RGB operation handle.
 * @param rgb_value RGB color value to set. (R: 0-255, G: 0-255, B: 0-255)
 * @return esp_err_t
 *     - ESP_OK: Success
 *     - ESP_ERR_INVALID_ARG: Invalid argument provided
 *     - ESP_FAIL: Failed to set brightness
 */
    static esp_err_t setRGB(void *hardware, uint32_t rgb_value);

/**
 * @brief Set the HSV color for the LED indicator.
 *
 * @param hardware LED indicator LED RGB operation handle.
 * @param hsv_value HSV color value to set. (H: 0-360, S: 0-255, V: 0-255)
 * @return esp_err_t
 *        - ESP_OK: Success
 *        - ESP_ERR_INVALID_ARG: Invalid argument provided
 *        - ESP_FAIL: Failed to set brightness
 */
    static esp_err_t setHSV(void *hardware, uint32_t hsv_value);

/**
 * @brief Set the brightness for the LED indicator.
 *
 * @param hardware_data Pointer to the LED indicator handle.
 * @param brightness Brightness value to set.
 * @return esp_err_t
 *     - ESP_OK: Success
 *     - ESP_FAIL: Failed to set brightness
 */
    static esp_err_t setBrightness(void *hardware_data, uint32_t brightness);
};