#include "SocketManager.h"

using namespace std;

void SocketManager::connectToSocket(const char *ip, const int port)
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

String SocketManager::getNextCommand()
{
    String lastLine;

    while (client.connected() && client.available())
    {
        lastLine = client.readStringUntil('\n');
        Serial.println(lastLine);
    }

    return lastLine;
};