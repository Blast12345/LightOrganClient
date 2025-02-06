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
            // delay(1000);
            attemptToConnect(ssid, password);
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

private:
    const char *const ssid;
    const char *const password;

    void wakeWifiHardware()
    {
        WiFi.setSleep(false);
    }

    void attemptToConnect(const char *ssid, const char *password)
    {
        Serial.println("Attempting to connect to WiFi...");
        WiFi.begin(ssid, password);
        delay(1000);

        if (isConnected())
        {
            printConnectionInformation();
        }
    }

    void printConnectionInformation()
    {
        Serial.println("Connection established.");
        Serial.println("SSID: " + WiFi.SSID());
        Serial.println("Signal strength: " + String(WiFi.RSSI()) + " dBm");
        Serial.println("IP address: " + WiFi.localIP().toString());
    }
};