#pragma once

#include <WiFi.h>
#include "NetworkCredentials.h"
#include "helpers/Wait.h"

class Network
{
public:
    Network(const NetworkCredentials &credentials) : credentials(credentials) {}

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
    const NetworkCredentials &credentials;

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