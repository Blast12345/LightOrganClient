#pragma once

#include <IPAddress.h>
#include "UdpSocket.h"
#include "ColorParser.h"

struct LOServer
{
private:
    UdpSocket socket;
    ColorParser colorParser;
    bool connected = false;

public:
    LOServer(int port) : socket(port) {}

    // TODO: Not a fan of this.
    void reset()
    {
        connected = false;
    }

    void connect()
    {
        socket.begin();
        connected = true;
    }

    bool isConnected()
    {
        return connected;
    }

    bool isDisconnected()
    {
        return !connected;
    }

    Color getNextColor()
    {
        std::string colorString = socket.getNextString();
        return colorParser.getColor(colorString);
    }
};