#include <Arduino.h>
#include <WiFi.h>

#pragma once

class WifiManager
{
public:
    boolean isConnected();
    boolean isDisconnected();
    void connect(const char *ssid, const char *password);
    void printConnectionInformation();
    boolean isReliableConnection();

private:
    void wakeWifiHardware();
    void attemptToConnect(const char *ssid, const char *password);
    void printSSID();
    void printSignalStrength();
    void printIpAddress();
};
