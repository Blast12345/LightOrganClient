#include <Arduino.h>
#include <WiFiUdp.h>

#pragma once

class SocketManager
{
public:
    void openPort(const int port);
    std::string getNextString();

private:
    void getNextPacket(char *packet);
};