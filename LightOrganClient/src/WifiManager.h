#include <Arduino.h>
#include <WiFi.h>

class WifiManager
{
public:
    static boolean isConnected();
    static void connect(const char *ssid, const char *password);
};
