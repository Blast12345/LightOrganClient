#include "SocketManager.h"
#include <WiFi.h>

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

void SocketManager::sendLedCount(const int count) {
    Serial.println("Preparing to set LED count.");

    String ledCountString = "LEDCOUNT=" + String(count);
    const char* array = ledCountString.c_str();
    client.write(array);

    Serial.println("Set LED count:" + ledCountString);
}

std::vector<RGB> SocketManager::getNextCommand()
{
    Serial.println("Checking for next command...");

    String message;

    // Flush any pending messages and listen for the next message.
    // We don't want to spend a bunch of time writing old data to the LED strip
    client.flush();
    while (client.connected() && message.length() == 0)
    {
        message = client.readStringUntil('\n');
    }

    // Create RGBs from the full message
    std::string messageC = message.c_str();
    return RGB::multipleFrom(messageC);
}

boolean SocketManager::isConnected() 
{
    return client.connected();
}