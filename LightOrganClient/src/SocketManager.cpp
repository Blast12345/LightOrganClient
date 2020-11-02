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

void SocketManager::sendLedCount(const int count) {
    Serial.println("Preparing to set LED count.");

    String ledCountString = "LEDCOUNT=" + String(count);
    const char* array = ledCountString.c_str();
    client.write(array);

    Serial.println("Set LED count:" + ledCountString);
}

std::vector<RGB> SocketManager::getNextCommand()
{  
    std::vector<RGB> output;
    Serial.println("Checking for next command...");

    unsigned int length = 300 * 3;
    uint8_t buffer[length];

    client.flush();
    while (client.connected() && client.available() < length)
    {
        delay(1);
    }

    Serial.println("Got data...");
    Serial.println(client.available());

    client.readBytes(buffer, length);
    
    //Process data
    // unsigned char temp[3];
    // for (uint i = 0; i < length; i+=3)
    // {
    //     temp[0] = buffer[i + 0];
    //     temp[1] = buffer[i + 1];
    //     temp[2] = buffer[i + 2];
    //     RGB color = RGB::singleFrom(temp);
    //     output.push_back(color);
    // }

    // unsigned long start = micros();
    // unsigned long end = micros();
    // Serial.println(end - start);
    delay(1000);

    return output;
}

boolean SocketManager::isConnected() 
{
    return client.connected();
}