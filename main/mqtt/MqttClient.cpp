#include "MqttClient.hpp"

static const char *TAG = "MQTT_CLIENT";

esp_mqtt_client_handle_t MqttClient::client = nullptr;

esp_err_t MqttClient::start() {
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    char client_id[50];
    snprintf(client_id, sizeof(client_id), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    esp_mqtt_client_config_t config = {};
    config.broker.address.uri = CONFIG_BROKER_URL;
    config.credentials.client_id = client_id;
    config.session.disable_clean_session = true;

    client = esp_mqtt_client_init(&config);
    esp_mqtt_client_register_event(client,
                                   esp_mqtt_event_id_t::MQTT_EVENT_ANY,
                                   &MqttEventHandler::handle,
                                   client);
    esp_mqtt_client_start(client);
    return ESP_OK;
}

esp_err_t MqttClient::publish(const std::string &topic) {
    return publish(topic, "");
}

esp_err_t MqttClient::publish(const std::string &topic, const std::string &payload) {
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    char t[50];
    snprintf(t, sizeof(t), "%02X:%02X:%02X:%02X:%02X:%02X%s",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], topic.c_str());
    auto msgId = esp_mqtt_client_publish(client, t, payload.c_str(), 0, 1, 0);
    ESP_LOGI(TAG, "Published topic '%s' msgId=%d", t, msgId);
    return ESP_OK;
}

string MqttClient::subscribe(const string &topic) {
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    char t[50];
    snprintf(t, sizeof(t), "%02X:%02X:%02X:%02X:%02X:%02X%s",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], topic.c_str());
    auto msgId = esp_mqtt_client_subscribe(client, t, 1);
    ESP_LOGI(TAG, "Subscribing topic '%s' msgId=%d", t, msgId);
    return t;
}
