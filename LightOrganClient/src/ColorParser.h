#include <Arduino.h>
#include "Color.h"
#include <vector>

#pragma once

class ColorParser
{

public:
    Color getColor(std::string message);

private:
    std::vector<uint8_t> getColorChannels(std::string message);
    Color getColor(std::vector<uint8_t> colorChannels);
    Color createDefaultColor();
};