#include "RGB.h"
#include <iostream>
#include <sstream>
#include <vector>

RGB RGB::fromMessage(std::string message)
{
    std::vector<int> colors;
    std::stringstream ss(message);

    //Populate the vector
    for (int i; ss >> i;)
    {
        colors.push_back(i);
        
        if (ss.peek() == ',')
        {
            ss.ignore();
        }
    }

    //Update our properties with the values if there is the appropriate number of values; 3 for RGB
    RGB output;

    if (colors.size() == 3)
    {
        output.red = colors[0];
        output.green = colors[1];
        output.blue = colors[2];
    } else {
        output.red = -1;
        output.green = -1;
        output.blue = -1;
    }

    return output;
}

boolean RGB::isValid() {
    return !(red == -1 || green == -1 || blue == -1);
}