#include <Arduino.h>

class CommandParser
{
public:
    static std::vector<uint32_t> parseCommand(std::string command);
};