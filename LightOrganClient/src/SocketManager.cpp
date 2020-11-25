#include "SocketManager.h"
#include <WiFi.h>

WiFiClient client;

boolean SocketManager::isConnected() 
{
    return client.connected();
}

void SocketManager::connectToSocket(const char *ip, const int port)
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

std::string SocketManager::getNextCommand()
{
    Serial.println("Checking for next command...");

    String message;

    // Flush any pending messages and listen for the next message.
    // We don't want to spend a bunch of time writing old data to the LED strip
    // client.flush();
    while (client.connected() && message.length() == 0)
    {
        message = client.readStringUntil('\n');
    }

    Serial.print("Remaining Characters: ");
    Serial.println(client.available());

    Serial.println("Retrieved next command...");

    return message.c_str();
}