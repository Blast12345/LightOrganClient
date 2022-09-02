#include <Arduino.h>

class SocketManager
{
public:
    void connectToSocket(const int port);
    std::string getNextString();

private:
    void printListeningMessage(const int port);
    void getNextPacket(char *packet);
};