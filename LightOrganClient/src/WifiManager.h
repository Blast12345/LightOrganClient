#include <Arduino.h>
#include <WiFi.h>

class WifiManager
{
public:
    static void connect(const char *ssid, const char *password);
    static boolean isConnected();
};
