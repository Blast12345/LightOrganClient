#include <Arduino.h>
#include <WiFi.h>

class WifiManager
{
public:
    void connectIfNeeded(const char *ssid, const char *password);
    boolean isConnected();
    void connect(const char *ssid, const char *password);

private:
    void configureWifiConnection();
    void startWifiConnection(const char *ssid, const char *password);
    void printConnectingMessage(const char *ssid);
    void waitForWifiConnection();
    void printTimeAwaited(int timeAwaited);
    void printConnectedMessage();
};
