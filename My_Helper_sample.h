#ifndef MY_HELPER_H
#define MY_HELPER_H

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_user = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";
const char* mqtt_server = "YOUR_MQTT_SERVER_ADDRESS";

const char* topic = "sonoff/pir";

const int inputPin = D1;//input pin is D3 in here but labelled D1 on the D1 mini
const int ledPin = D4;

#endif
