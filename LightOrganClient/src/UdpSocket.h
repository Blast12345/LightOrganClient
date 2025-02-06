#pragma once

#include <WiFi.h>

class UdpSocket
{
private:
    WiFiUDP udp;
    const int port;

public:
    UdpSocket(const int port) : port(port) {}

    void begin()
    {
        udp.begin(port);
        Serial.println("Began listening on port: " + String(port));
    }

    std::string getNextString()
    {
        Serial.println("Getting next string...");

        char packet[255];
        getNextPacket(packet);
        Serial.println("String recieved: " + String(packet));

        return std::string(packet);
    }

private:
    void getNextPacket(char *packet)
    {
        while (true)
        {
            int packetSize = udp.parsePacket();

            if (packetSize)
            {
                int len = udp.read(packet, 255);
                packet[len] = '\0';
                break;
            }
        }
    }
};