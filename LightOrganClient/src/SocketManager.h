#include <Arduino.h>

class SocketManager
{
public:
    void connectToSocket(const int port);
    void getNextColor();

private:
    void printListeningMessage(const int port);
};