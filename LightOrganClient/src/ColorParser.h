#include <Arduino.h>
#include "OrganColor.h"
#include <vector>

class ColorParser
{

public:
    OrganColor getColor(std::string message);

private:
    std::vector<uint8_t> getColorChannels(std::string message);
    OrganColor getColor(std::vector<uint8_t> colorChannels);
    OrganColor createDefaultColor();
};