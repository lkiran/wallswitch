set(SOURCES
        app_main.cpp
        mqtt/MqttClient.cpp
        wifi/WifiConnection.cpp
        mqtt/handlers/MqttEventHandler.cpp
        wallswitch/Wallswitch.cpp
        rgbLed/RgbLed.cpp
        rgbLed/driver/CustomRGBDriver.cpp
        rgbLed/color/RGB.cpp
        rgbLed/color/RGBA.cpp
        haptic/Haptic.cpp
        temperature/Temperature.cpp
)

set(INCLUDES
        .
        events
        wifi
        mqtt
        mqtt/handlers
        wallswitch
        rgbLed
        rgbLed/driver
        rgbLed/color
        haptic
        temperature
        )

idf_component_register(
        SRCS ${SOURCES}
        INCLUDE_DIRS ${INCLUDES}
)
