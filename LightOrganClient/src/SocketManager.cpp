#include "SocketManager.h"
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

void SocketManager::connectToSocket(const int port)
{
    udp.begin(port);
    printListeningMessage(port);
}

void SocketManager::printListeningMessage(const int port)
{
    Serial.print("Began listening on port ");
    Serial.println(port);
}

std::string SocketManager::getNextString()
{
    Serial.println("Getting next string...");
    char packetBuffer[255];
    getNextPackets(packetBuffer);
    Serial.println(packetBuffer);
    Serial.println("String recieved...");
    return std::string(packetBuffer);
}

void SocketManager::getNextPackets(char *outputBuffer)
{
    bool thisPacketIsNotEmpty = false;
    bool previousPacketIsLoaded = false;

    while (true)
    {
        thisPacketIsNotEmpty = (udp.parsePacket() > 0);

        if (thisPacketIsNotEmpty)
        { // raise flag that a packet is loaded and read it in the buffer
            previousPacketIsLoaded = true;
            int bufferSize = sizeof(outputBuffer);
            udp.read(outputBuffer, bufferSize);
        }
        else if (!thisPacketIsNotEmpty && previousPacketIsLoaded)
        { // if the current packet is empty, but a loaded packet exists, break out of the loop
            previousPacketIsLoaded = false;
            break;
        }
    }
}
