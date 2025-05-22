#pragma once

#include <Arduino.h>
#include "Color.h"
#include "Colors.h"
#include <sstream>
#include <vector>

class ColorParser
{
public:
    static auto getColor(const std::string &message) -> Color
    {
        std::vector<unsigned int> colorChannels = getColorChannels(message);

        if (colorChannels.size() == 3)
        {
            return getColor(colorChannels);
        }
        else
        {
            return Colors::Black;
        }
    }

private:
    static auto getColorChannels(const std::string &message) -> std::vector<unsigned int>
    {
        std::vector<unsigned int> colorChannels;
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

    static auto getColor(const std::vector<unsigned int> &colorChannels) -> Color
    {
        return Color(colorChannels[0], colorChannels[1], colorChannels[2]);
    }
};
