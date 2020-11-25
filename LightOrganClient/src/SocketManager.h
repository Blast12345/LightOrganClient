#include <Arduino.h>

class SocketManager
{
public:
    boolean isConnected();
    void connectToSocket(const char *ip, const int port);
    void sendLedCount(const int count);
    std::string getNextCommand();
};