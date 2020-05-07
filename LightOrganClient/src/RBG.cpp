#include "RGB.h"
#include <sstream>

std::vector<RGB> RGB::multipleFrom(std::string message)
{
    std::vector<std::string> colorStrings;
    std::stringstream s_stream(message);

    // Split our message into individual color strings
    while (s_stream.good())
    {
        std::string led;
        getline(s_stream, led, '|');
        colorStrings.push_back(led);
    }

    // Loop over each color string and generate the appropriate RGB instance
    std::vector<RGB> output;

    for (uint i = 0; i < colorStrings.size(); i++)
    {
        std::string colorString = colorStrings[i];
        RGB color = RGB::singleFrom(colorString);
        output.push_back(color);
    }

    return output;
}

RGB RGB::singleFrom(std::string message)
{
    std::vector<int> colorChannels;
    std::stringstream s_stream(message);

    // Get the RGB channels from the message
    for (int i; s_stream >> i;)
    {
        colorChannels.push_back(i);

        if (s_stream.peek() == ',')
        {
            s_stream.ignore();
        }
    }

    // Update our properties with the values if there is the appropriate number of values; 3 for RGB
    RGB output;

    if (colorChannels.size() == 3)
    {
        output.red = colorChannels[0];
        output.green = colorChannels[1];
        output.blue = colorChannels[2];
    }
    else
    {
        output.red = 0;
        output.green = 0;
        output.blue = 0;
    }

    return output;
}