#include "SocketManager.h"
#include <ESP8266WiFi.h>

WiFiClient client;

void SocketManager::connectToSocket(const char *ip, const int port)
{
    Serial.println("Connecting to socket");

    if (client.connect(ip, port))
    {
        Serial.println("Connected to socket");
        client.flush();
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

std::vector<RGB> SocketManager::getNextCommand(int ledCount)
{  
    // Serial.println("Checking for next command...");
    std::vector<RGB> output;
    
    // Our buffer length is 3x the number of LEDs because each LED will have 3 bytes of color information
    // Serial.println("Creating buffer...");
    unsigned int length = 3 * ledCount;
    uint8_t buffer[length];

    // Wait until a full data frame (length) becomes available
    // wdt_enable(WDTO_8S);
    // Serial.println("Watching for available data...");
    while (client.connected() && client.available() < length) { delay(1); }

    // Read the data from the client
    // Serial.println("Preparing to read data...");
    // Serial.println(client.available());
    client.readBytes(buffer, length);
    // Serial.println(client.available());

    if (client.available() > 900) {
        Serial.println("WARNING: Extra frame data left over in the client. This deviced is saturated with too much data.");
    }

    // Process data
    // Serial.println("Preparing to process data...");
    uint8_t temp[3];
    for (uint i = 0; i < ledCount; i+=3)
    {
        temp[0] = buffer[i + 0];
        temp[1] = buffer[i + 1];
        temp[2] = buffer[i + 2];
        RGB color = RGB::singleFrom(temp);
        output.push_back(color);
    }

    return output;
}

boolean SocketManager::isConnected() 
{
    return client.connected();
}





