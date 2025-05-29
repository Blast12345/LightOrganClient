#pragma once

#include "NetworkCredentials.h"
#include "helpers/Wait.h"
#include <WiFi.h>

class Network
{
private:
    const NetworkCredentials credentials;

public:
    explicit Network(const NetworkCredentials credentials) : credentials(credentials) {}

    void connect()
    {
        wakeWifiHardware();

        while (isDisconnected())
        {
            attemptToConnect();
            waitOneSecond();
        }
    }

    auto isConnected() -> boolean
    {
        return WiFi.isConnected() == true;
    }

    auto isDisconnected() -> boolean
    {
        return WiFi.isConnected() == false;
    }

    auto printConnectionInformation() -> void
    {
        Serial.println("Connection established.");
        Serial.println("SSID: " + WiFi.SSID());
        Serial.println("Signal strength: " + String(WiFi.RSSI()) + " dBm");
        Serial.println("IP address: " + WiFi.localIP().toString());
    }

private:
    void wakeWifiHardware()
    {
        WiFi.setSleep(false);
    }

    void attemptToConnect()
    {
        Serial.print("Attempting to connect to WiFi...");
        WiFi.begin(credentials.ssid, credentials.password);

        while (isDisconnected())
        {
            Serial.println(".");
            waitOneSecond();
        }
    }
};