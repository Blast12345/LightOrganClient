#pragma once

#include <WiFi.h>

class Network
{
public:
    Network(const char *ssid, const char *password) : ssid(ssid), password(password) {}

    void connect()
    {
        wakeWifiHardware();

        while (isDisconnected())
        {
            attemptToConnect(ssid, password);
            delay(1000);
        }
    }

    boolean isConnected()
    {
        return WiFi.isConnected() == true;
    }

    boolean isDisconnected()
    {
        return WiFi.isConnected() == false;
    }

    void printConnectionInformation()
    {
        Serial.println("Connection established.");
        Serial.println("SSID: " + WiFi.SSID());
        Serial.println("Signal strength: " + String(WiFi.RSSI()) + " dBm");
        Serial.println("IP address: " + WiFi.localIP().toString());
    }

private:
    const char *const ssid;
    const char *const password;

    void wakeWifiHardware()
    {
        WiFi.setSleep(false);
    }

    void attemptToConnect(const char *ssid, const char *password)
    {
        Serial.print("Attempting to connect to WiFi...");
        WiFi.begin(ssid, password);

        while (isDisconnected())
        {
            Serial.println(".");
            delay(1000);
        }
    }
};