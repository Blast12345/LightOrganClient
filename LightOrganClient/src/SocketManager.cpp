#include "SocketManager.h"
#include <WiFiUdp.h>
#include <WiFi.h>

WiFiUDP udp;
char packet[255];
char reply[] = "Packet received!";

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

void SocketManager::getNextColor()
{
    udp.begin(9999);
    
    Serial.println("Getting next color...");

    while (udp.parsePacket() == 0)
    {
        int packetSize = udp.parsePacket();
        if (packetSize)
        {
            Serial.print("Received packet! Size: ");
            Serial.println(packetSize);
            int len = udp.read(packet, 255);
            if (len > 0)
            {
                packet[len] = '\0';
            }
            Serial.print("Packet received: ");
            Serial.println(packet);
        }
    }
    // // Serial.println("Checking for next command...");

    // unsigned long start = micros();

    // // TODO: Flush isn't working
    // // flush(): fail on fd 56, errno: 11, "No more processes"
    // // client.flush();

    // // We need to read in our next command; wait until command is available.
    // String message;
    // while (client.connected() && message.length() == 0)
    // {
    //     message = client.readStringUntil('\n');
    // }

    // unsigned long end = micros();
    // Serial.print("Time: ");
    // Serial.println(end - start);

    // // Serial.println("Retrieved next command...");

    // return message.c_str();
}