#include "RgbLed.hpp"
#include "CustomRGBDriver.hpp"
#include "MqttClient.hpp"
#include "RGB.hpp"

static const char *TAG = "RGB_LED";

enum {
    BLINK_DOUBLE_RED = 0,
    BLINK_COLOR_HSV_RING,
    BLINK_COLOR_HSV_RING_REV,
    BLINK_MAX,
};

static const blink_step_t double_red_blink[] = {
        /*!< Set color to red by R:255 G:0 B:0 */
        {LED_BLINK_RGB, SET_RGB(255, 0, 0), 0},
        {LED_BLINK_HOLD, LED_STATE_ON,      500},
        {LED_BLINK_HOLD, LED_STATE_OFF,     500},
        {LED_BLINK_HOLD, LED_STATE_ON,      500},
        {LED_BLINK_HOLD, LED_STATE_OFF,     500},
        {LED_BLINK_LOOP, 0,                 0},
};
static const blink_step_t color_hsv_ring_blink[] = {
        /*!< Set Color to RED */
        {LED_BLINK_HSV,      SET_HSV(0, MAX_SATURATION, MAX_BRIGHTNESS),       0},
        {LED_BLINK_HSV_RING, SET_HSV(MAX_HUE, MAX_SATURATION, MAX_BRIGHTNESS), 6000},
        {LED_BLINK_LOOP, 0,                                                    0},
};
static const blink_step_t color_hsv_ring_rev[] = {
        /*!< Set Color to RED */
        {LED_BLINK_HSV,      SET_HSV(MAX_HUE, MAX_SATURATION, MAX_BRIGHTNESS), 0},
        {LED_BLINK_HSV_RING, SET_HSV(0, MAX_SATURATION, MAX_BRIGHTNESS),       6000},
        {LED_BLINK_LOOP, 0,                                                    0},
};

blink_step_t const *led_mode[] = {
        [BLINK_DOUBLE_RED] = double_red_blink,
        [BLINK_COLOR_HSV_RING] = color_hsv_ring_blink,
        [BLINK_COLOR_HSV_RING_REV] = color_hsv_ring_rev,
        [BLINK_MAX] = nullptr,
};

map<string, RgbLed> RgbLed::instances = {};

RgbLed *RgbLed::getInstance(const string &topic) {
    size_t titlePosition = topic.rfind('/');
    if (titlePosition == std::string::npos)
        return nullptr;

    string title = topic.substr(titlePosition + 1);
    auto it = instances.find(title);
    if (it == instances.end()) {
        ESP_LOGW(TAG, "No instance have been found for title=%s", title.c_str());
        std::string keysList;
        for (const auto &pair: instances) {
            keysList += "\t> " + pair.first + "\n";
        }
        ESP_LOGI(TAG, "List of available titles:\n%s", keysList.c_str());

        return nullptr;
    }
    return &(it->second);
}

string RgbLed::getTitle() {
    ESP_LOGI(TAG, "RgbLed title=%s", title.c_str());
    return this->title;
}

RgbLed::RgbLed(const string &title, gpio_num_t redPin, gpio_num_t greenPin, gpio_num_t bluePin)
        : title(title) {
    auto *hw = new custom_led_rgb_t;
    hw->gpio[RED] = redPin;
    hw->gpio[GREEN] = greenPin;
    hw->gpio[BLUE] = bluePin;

    led_indicator_custom_config_t driver = {
            .is_active_level_high = false,
            .duty_resolution = LED_DUTY_8_BIT,
            .hal_indicator_init = CustomRGBDriver::init,
            .hal_indicator_set_on_off = CustomRGBDriver::setOnOff,
            .hal_indicator_deinit = CustomRGBDriver::deinit,
            .hal_indicator_set_brightness = CustomRGBDriver::setBrightness,
            .hal_indicator_set_rgb = CustomRGBDriver::setRGB,
            .hal_indicator_set_hsv = CustomRGBDriver::setHSV,
            .hardware_data = hw
    };

    auto *config = new led_indicator_config_t;
    config->mode = LED_CUSTOM_MODE;
    config->led_indicator_custom_config = &driver;
    config->blink_lists = led_mode;
    config->blink_list_num = BLINK_MAX;

    this->handle = led_indicator_create(config);
    RgbLed::instances.insert({title, *this});
}

void RgbLed::setRgb(string &color) {
    auto rgb = RGB(color);
    led_indicator_set_rgb(handle, SET_RGB(rgb.getRed(), rgb.getGreen(), rgb.getBlue()));
}

void RgbLed::subscribeAll() {
    for (const auto &pair: instances) {
        string topic = MqttClient::subscribe("/led/" + pair.first);
    }

}

