#include <Arduino.h>
#include <WiFiUdp.h>

#pragma once

class SocketManager
{
public:
    void openPort(IPAddress serverIP, int serverPort);
    std::string getNextString();

private:
    bool getNextPacket(char *packet);
};