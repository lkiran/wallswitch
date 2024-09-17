# Wallswitch
ESP32 based wallswitch

# ESP-MQTT sample application
(See the README.md file in the upper level 'examples' directory for more information about examples.)

This example connects to the broker URI selected using `idf.py menuconfig` (using mqtt tcp transport) and as a demonstration subscribes/unsubscribes and send a message on certain topic.
(Please note that the public broker is maintained by the community so may not be always available, for details please see this [disclaimer](https://iot.eclipse.org/getting-started/#sandboxes))

Note: If the URI equals `FROM_STDIN` then the broker address is read from stdin upon application startup (used for testing)

It uses ESP-MQTT library which implements mqtt client to connect to mqtt broker.

## How to use example

### Hardware Required

This example can be executed on any ESP32 board, the only required interface is WiFi and connection to internet.

### Configure the project

* Open the project configuration menu (`idf.py menuconfig`)
* Configure Wi-Fi or Ethernet under "Example Connection Configuration" menu. See "Establishing Wi-Fi or Ethernet Connection" section in [examples/protocols/README.md](../../README.md) for more details.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.


## Sketch
![Fritzing Sketch](https://github.com/lkiran/wallswitch/blob/master/wallswitch_bb.png)

## Example Output

```bash
I MAIN: Startup...
I MAIN: Free memory: 273708 bytes
I MAIN: IDF version: v5.3-dev-2489-g60a2bf6a68
I WALLSWITCH: Button callbacks are registered for top-left
I WALLSWITCH: Button callbacks are registered for top-right
I WALLSWITCH: Button callbacks are registered for bottom-left
I WALLSWITCH: Button callbacks are registered for bottom-right
I WIFI: Start connect.
I WIFI: Connecting to KIRAN 2.4GHz...
I WIFI: Waiting for IP(s)
I WIFI: Got IPv4 event: Interface "WiFi" address: 1.0.0.12
I MQTT_CLIENT: Subscribing topic '44:FF:22:AA:BB:88/led/bottom-left' msgId=1234
I MQTT_CLIENT: Subscribing topic '44:FF:22:AA:BB:88/led/bottom-right' msgId=1234
I MQTT_CLIENT: Subscribing topic '44:FF:22:AA:BB:88/led/top-left' msgId=1234 
I MQTT_CLIENT: Subscribing topic '44:FF:22:AA:BB:88/led/top-right' msgId=1234
I MQTT_HANDLER: Published topic '44:FF:22:AA:BB:88/start' msg_id=1234
I MQTT_HANDLER: MQTT_EVENT_SUBSCRIBED, msg_id=1234
I MQTT_HANDLER: MQTT_EVENT_SUBSCRIBED, msg_id=1234
I MQTT_HANDLER: MQTT_EVENT_SUBSCRIBED, msg_id=1234
I MQTT_HANDLER: MQTT_EVENT_SUBSCRIBED, msg_id=1234
I MQTT_HANDLER: MQTT_EVENT_PUBLISHED, msg_id=1234
I MQTT_HANDLER: MQTT_EVENT_DATA
I MQTT_HANDLER: TOPIC=44:FF:22:AA:BB:88/led/bottom-right
I MQTT_HANDLER: DATA=#00aa00
I MQTT_HANDLER: MQTT_EVENT_DATA
I MQTT_HANDLER: TOPIC=44:FF:22:AA:BB:88/led/bottom-left
I MQTT_HANDLER: DATA=#00aa00
I MQTT_HANDLER: MQTT_EVENT_DATA
I MQTT_HANDLER: TOPIC=44:FF:22:AA:BB:88/led/top-right
I MQTT_HANDLER: DATA=#00aa00
I MQTT_HANDLER: MQTT_EVENT_DATA
I MQTT_HANDLER: TOPIC=44:FF:22:AA:BB:88/led/top-left
I MQTT_HANDLER: DATA=#00aa00
I WALLSWITCH: Button (top-left) is pressed
I HAPTIC: Poking once
I WALLSWITCH: Button (top-left) is clicked
I MQTT_CLIENT: Published topic '44:FF:22:AA:BB:88/button/top-left' msgId=1234
I MQTT_HANDLER: MQTT_EVENT_PUBLISHED, msg_id=1234
I MQTT_HANDLER: MQTT_EVENT_DATA
I MQTT_HANDLER: TOPIC=44:FF:22:AA:BB:88/led/top-left
I MQTT_HANDLER: DATA=#aaaa00
```
