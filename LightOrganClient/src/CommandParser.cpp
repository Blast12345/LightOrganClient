#include "CommandParser.h"
#include <sstream>

std::vector<uint32_t> CommandParser::parseCommand(std::string command)
{
    Serial.println("Parsing command...");

    // Split our command into individual hex codes
    std::vector<std::string> hexCodes;
    std::stringstream s_stream(command);

    while (s_stream.good())
    {
        std::string led;
        getline(s_stream, led, '|');
        hexCodes.push_back(led);
    }

    // Convert those hex codes into numbers
    // TODO: Is there a better term than "numbers"? It feels like their ought to be a specific term for a hex represented as an int.
    std::vector<uint32_t> colors;

    for (uint i = 0; i < hexCodes.size(); i++)
    {
        std::string codeString = hexCodes[i];
        uint32_t codeLong = strtol(codeString.c_str(), NULL, 16);
        colors.push_back(codeLong);
    }

    Serial.println("Finished parsing command...");

    return colors;
}