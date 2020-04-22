#include <Arduino.h>
#include <ESP8266WiFi.h>

class WifiManager
{
public:
    static void connect(const char *ssid, const char *password);
};
