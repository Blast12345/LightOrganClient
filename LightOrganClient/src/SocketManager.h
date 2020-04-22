#include <Arduino.h>
#include "RGB.h"

class SocketManager
{
public:
    void connectToSocket(const char *ip, const int port);
    RGB getNextCommand();
};