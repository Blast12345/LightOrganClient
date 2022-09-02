#include "Color.h" 
#include "ColorParser.h"
#include <sstream>
#include <vector>

Color ColorParser::getColor(std::string message)
{
    std::vector<uint8_t> colorChannels = getColorChannels(message);

    if (colorChannels.size() == 3)
    {
        return getColor(colorChannels);
    }
    else
    {
        return createDefaultColor();
    }
}

std::vector<uint8_t> ColorParser::getColorChannels(std::string message)
{
    std::vector<uint8_t> colorChannels;
    std::stringstream s_stream(message);

    for (int i; s_stream >> i;)
    {
        colorChannels.push_back(i);

        if (s_stream.peek() == ',')
        {
            s_stream.ignore();
        }
    }

    return colorChannels;
}

Color ColorParser::getColor(std::vector<uint8_t> colorChannels)
{
    Color newColor;
    newColor.red = colorChannels[0];
    newColor.green = colorChannels[1];
    newColor.blue = colorChannels[2];
    return newColor;
}

Color ColorParser::createDefaultColor()
{
    Color newColor;
    newColor.red = 0;
    newColor.green = 0;
    newColor.blue = 0;
    return newColor;
}