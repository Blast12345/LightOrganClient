#include "SocketManager.h"
#include <ESP8266WiFi.h>

WiFiClient client;

void SocketManager::connectToSocket(const char *ip, const int port) //TODO: Add an LED could to send to the socket server
{
    Serial.println("Connecting to socket");

    if (client.connect(ip, port))
    {
        Serial.println("Connected to socket");
    }
    else
    {
        Serial.println("Failed to connect to socket");
    }
}

RGB SocketManager::getNextCommand()
{
    String lastLine;

    // Flush any pending messages and listen for the next message.
    // We don't want to spend a bunch of time writing old data to the LED strip
    client.flush();
    while (client.connected() && lastLine.length() == 0)
    {
        lastLine = client.readStringUntil('\n');
    }

    // Convert from String to std::string
    const char *array = lastLine.c_str();
    std::string output = array;

    // Create an RGB struct given the string
    return RGB::fromMessage(output);
};
