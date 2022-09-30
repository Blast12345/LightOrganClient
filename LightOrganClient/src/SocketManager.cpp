#include "SocketManager.h"

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
    char packet[255];
    getNextPacket(packet);
    Serial.println(packet);
    Serial.println("String recieved...");
    return std::string(packet);
}

void SocketManager::getNextPacket(char *packet)
{
    while (true) {
        int packetSize = udp.parsePacket();

        if (packetSize)
        {
            int len = udp.read(packet, 255);
            packet[len] = '\0';
            break;
        }
    }
}
