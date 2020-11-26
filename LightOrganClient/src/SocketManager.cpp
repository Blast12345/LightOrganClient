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

void SocketManager::sendLedCount(const int count)
{
    Serial.println("Preparing to set LED count.");

    String ledCountString = "LEDCOUNT=" + String(count);
    const char *array = ledCountString.c_str();
    client.write(array);

    Serial.println("Set LED count:" + ledCountString);
}

bool test = false;

std::string SocketManager::getNextCommand()
{
    unsigned long start = micros();

    // Serial.println("Checking for next command...");

    // TODO: Flush isn't working
    // flush(): fail on fd 56, errno: 11, "No more processes"
    // client.flush();

    // We need to read in our next command; wait until command is available.
    String message;
    while (client.connected() && message.length() == 0)
    {
        message = client.readStringUntil('\n');
        // while (client.available() > 0 && client.find('\n')) {
        //     message = client.readStringUntil('\n');
        // }
    }

    // Serial.println(message);
    // Serial.println("Retrieved next command...");
    unsigned long end = micros();
    Serial.print("Time: ");
    Serial.println(end - start);

    return message.c_str();
}