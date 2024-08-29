#include "SocketManager.h"
#include <WiFiUdp.h>
#include <WiFi.h>
#include <ESPmDNS.h>

WiFiClient client;
IPAddress serverIP(192, 168, 1, 101); // Predefined server IP address

void connectToServer(IPAddress serverIP, uint16_t serverPort)
{
    Serial.print("Connecting to server at ");
    Serial.print(serverIP);
    Serial.print(":");
    Serial.println(serverPort);

    for (int attempt = 1; attempt <= 3; ++attempt)
    {
        if (client.connect(serverIP, serverPort))
        {
            Serial.println("Connected to server!");
            client.println("Hello from ESP32!"); // Example message to send to server
            return;                              // Exit after successful connection
        }
        else
        {
            Serial.print("Connection attempt ");
            Serial.print(attempt);
            Serial.println(" failed.");
            delay(1000); // Wait 1 second before retrying
        }
    }

    Serial.println("All connection attempts failed.");
}

void SocketManager::openPort(const int port)
{
    if (client.connected())
    {
        Serial.println("Already connected to a server.");
        return;
    }

    if (!MDNS.begin("esp32"))
    { // The name of the device (you can use any name)
        Serial.println("Error starting mDNS");
        return;
    }
    Serial.println("mDNS responder started");

    connectToServer(serverIP, port);
}

bool SocketManager::getNextPacket(char *packet)
{
    return true;
}

std::string SocketManager::getNextString()
{
    return "0,0,0";
}