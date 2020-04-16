#include <Arduino.h>
#include <ESP8266WiFi.h>

class SocketManager
{

public:
    WiFiClient client;
    void connectToSocket(const char *ip, const int port);
    String getNextCommand();
};