#pragma once

#include <IPAddress.h>
#include <AsyncUDP.h>
#include "ColorParser.h"

struct LOServer
{
private:
    const int port;
    AsyncUDP udp;
    ColorParser colorParser;
    bool listening = false;
    std::function<void(Color)> nextColorCallback;

public:
    explicit LOServer(int port) : port(port), udp(), colorParser() {}

    void beginListening()
    {
        Serial.println("Connecting to server...");
        startListening();
        startHandlingPackets();
    }

    bool isListening()
    {
        return listening;
    }

    bool isNotListening()
    {
        return !listening;
    }

    void onNextColor(std::function<void(Color)> callback)
    {
        nextColorCallback = callback;
    }

private:
    void startListening()
    {
        listening = udp.listen(port);

        if (listening)
        {
            Serial.println("Began listening on port: " + String(port));
        }
        else
        {
            throw std::runtime_error("Failed to begin listening on port: " + std::to_string(port));
        }
    }

    void startHandlingPackets()
    {
        udp.onPacket([this](AsyncUDPPacket packet)
                     { handlePacket(packet); });
    }

    void handlePacket(AsyncUDPPacket packet)
    {
        // I may add support for other message types in the future.
        Serial.println("Packet received.");
        Color nextColor = getNextColor(packet);
        if (nextColorCallback)
        {
            nextColorCallback(nextColor);
        }
    }
    Color getNextColor(AsyncUDPPacket packet)
    {
        std::string colorString(reinterpret_cast<const char *>(packet.data()), packet.length());
        return colorParser.getColor(colorString);
        // std::string colorString = socket.getNextString();
        // return colorParser.getColor(colorString);
    }
};