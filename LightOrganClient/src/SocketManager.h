#include <Arduino.h>
#include "RGB.h"

class SocketManager
{
public:
    void connectToSocket(const char *ip, const int port);
    void sendLedCount(const int count);
    std::vector<RGB> getNextCommand();
    boolean isConnected();
};