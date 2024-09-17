#include <cstring>
#include "WifiConnection.hpp"
#include "esp_log.h"

static const char *TAG = "WIFI";
static esp_netif_t *station_networkinterface = nullptr;
static SemaphoreHandle_t semaphore_get_ip_address = nullptr;

#if CONFIG_CONNECT_WIFI
#define NETWORK_INTERFACE_DESCRIPTION_STATION "WiFi"
#endif

#if CONFIG_WIFI_SCAN_METHOD_FAST
#define WIFI_SCAN_METHOD WIFI_FAST_SCAN
#elif CONFIG_WIFI_SCAN_METHOD_ALL_CHANNEL
#define WIFI_SCAN_METHOD WIFI_ALL_CHANNEL_SCAN
#endif

#if CONFIG_WIFI_CONNECT_AP_BY_SIGNAL
#define WIFI_CONNECT_AP_SORT_METHOD WIFI_CONNECT_AP_BY_SIGNAL
#elif CONFIG_WIFI_CONNECT_AP_BY_SECURITY
#define WIFI_CONNECT_AP_SORT_METHOD WIFI_CONNECT_AP_BY_SECURITY
#endif

#if CONFIG_WIFI_AUTH_OPEN
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_WIFI_AUTH_WEP
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_WIFI_AUTH_WPA_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_WIFI_AUTH_WPA2_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_WIFI_AUTH_WPA_WPA2_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_WIFI_AUTH_WPA2_ENTERPRISE
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_ENTERPRISE
#elif CONFIG_WIFI_AUTH_WPA3_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_WIFI_AUTH_WPA2_WPA3_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_WIFI_AUTH_WAPI_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif

static void handler_on_wifi_disconnect(void *arg, esp_event_base_t base,
                                       int32_t event_id, void *event_data) {
    ESP_LOGI(TAG, "Wi-Fi disconnected, trying to reconnect...");
    esp_err_t err = esp_wifi_connect();
    if (err == ESP_ERR_WIFI_NOT_STARTED) {
        return;
    }
    ESP_ERROR_CHECK(err);
}

static void handler_on_wifi_connect(void *esp_netif, esp_event_base_t event_base,
                                    int32_t event_id, void *event_data) {

}

/**
 * @brief Checks the netif description if it contains specified prefix.
 * All netifs created withing common connect component are prefixed with the module TAG,
 * so it returns true if the specified netif is owned by this module
 */
bool is_our_network_interface(const char *prefix, esp_netif_t *netif) {
    return strncmp(prefix, esp_netif_get_desc(netif), strlen(prefix) - 1) == 0;
}

static void handler_on_station_got_ip(void *arg, esp_event_base_t event_base,
                                      int32_t event_id, void *event_data) {
    auto *event = (ip_event_got_ip_t *) event_data;
    if (!is_our_network_interface(NETWORK_INTERFACE_DESCRIPTION_STATION, event->esp_netif)) {
        return;
    }
    ESP_LOGI(TAG, "Got IPv4 event: Interface \"%s\" address: " IPSTR, esp_netif_get_desc(event->esp_netif),
             IP2STR(&event->ip_info.ip));
    if (semaphore_get_ip_address) {
        xSemaphoreGive(semaphore_get_ip_address);
    } else {
        ESP_LOGI(TAG, "- IPv4 address: " IPSTR ",", IP2STR(&event->ip_info.ip));
    }
}


void WifiConnection::start(void) {
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));

    esp_netif_inherent_config_t interface_config = ESP_NETIF_INHERENT_DEFAULT_WIFI_STA();
    interface_config.if_desc = NETWORK_INTERFACE_DESCRIPTION_STATION;
    interface_config.route_prio = 128;
    station_networkinterface = esp_netif_create_wifi(WIFI_IF_STA, &interface_config);
    esp_wifi_set_default_wifi_sta_handlers();

    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void WifiConnection::stop() {
    esp_err_t err = esp_wifi_stop();
    if (err == ESP_ERR_WIFI_NOT_INIT) {
        return;
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(esp_wifi_deinit());
    ESP_ERROR_CHECK(esp_wifi_clear_default_wifi_driver_and_handlers(station_networkinterface));
    esp_netif_destroy(station_networkinterface);
    station_networkinterface = nullptr;
}

void WifiConnection::shutdown_handler() {
    ESP_ERROR_CHECK(
            esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &handler_on_wifi_disconnect));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &handler_on_station_got_ip));
    ESP_ERROR_CHECK(
            esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &handler_on_wifi_connect));
    if (semaphore_get_ip_address) {
        vSemaphoreDelete(semaphore_get_ip_address);
    }
    esp_wifi_disconnect();
    stop();
}

esp_err_t WifiConnection::connect() {
#if !CONFIG_CONNECT_WIFI
    return ESP_OK;
#endif
    ESP_LOGI(TAG, "Start connect.");
    start();
    wifi_config_t config = {
            .sta = { // station
                    .ssid = CONFIG_WIFI_SSID,
                    .password = CONFIG_WIFI_PASSWORD,
                    .scan_method = WIFI_SCAN_METHOD,
                    .sort_method = WIFI_CONNECT_AP_SORT_METHOD,
                    .threshold = {
                            .rssi = CONFIG_WIFI_SCAN_RSSI_THRESHOLD,
                            .authmode = WIFI_SCAN_AUTH_MODE_THRESHOLD,
                    }
            },
    };
    semaphore_get_ip_address = xSemaphoreCreateBinary();
    if (semaphore_get_ip_address == nullptr) {
        return ESP_ERR_NO_MEM;
    }

    ESP_ERROR_CHECK(
            esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &handler_on_wifi_disconnect,
                                       nullptr));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &handler_on_station_got_ip, nullptr));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &handler_on_wifi_connect,
                                               station_networkinterface));

    ESP_LOGI(TAG, "Connecting to %s...", config.sta.ssid);
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &config));
    esp_err_t ret = esp_wifi_connect();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "WiFi connect failed! ret:%x", ret);
        return ret;
    }

    ESP_LOGI(TAG, "Waiting for IP(s)");
    xSemaphoreTake(semaphore_get_ip_address, portMAX_DELAY);

    ESP_ERROR_CHECK(esp_register_shutdown_handler(&shutdown_handler));
    return ESP_OK;
}
