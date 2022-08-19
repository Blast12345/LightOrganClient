#include <Arduino.h>
#include <vector>

class CommandParser
{
public:
    static std::vector<uint32_t> parseCommand(std::string command);
};