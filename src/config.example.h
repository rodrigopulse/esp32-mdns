#pragma once

#include <Arduino.h>

const char *WIFI_SSID = "SSID";
const char *WIFI_PASSWORD = "PASSWORD";
const char *MDNS_HOSTNAME = "esp32";

const IPAddress STATIC_IP(192, 168, 0, 100);
const IPAddress GATEWAY_IP(192, 168, 0, 1);
const IPAddress SUBNET_MASK(255, 255, 255, 0);
