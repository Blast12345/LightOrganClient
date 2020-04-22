#include "SocketManager.h"

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

    // Grab the latest string; multiple may be waiting, but we only want the absolute newest.
    while (client.connected() && client.available())
    {
        lastLine = client.readStringUntil('\n');
        Serial.println(lastLine);
    }

    // Convert from String to std::string
    const char *array = lastLine.c_str();
    std::string output = array;

    // Create an RGB struct given the string
    return RGB::fromMessage(output);
};
