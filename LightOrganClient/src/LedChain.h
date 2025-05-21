#pragma once

#include "Color.h"
#include <FastLED.h>
#include <vector>
#include "LedSegment.h"
#include "Voltage.h"
#include "Amperage.h"

template <unsigned int PIN>
class LedChain
{
private:
    Voltage voltage;
    Amperage amperage;
    std::vector<LedSegment> segments;

public:
    LedChain(Voltage voltage, Amperage amperage, const std::vector<LedSegment> &segments)
        : voltage(voltage), amperage(amperage), segments(segments) {}

    void setup()
    {
        for (auto &segment : segments)
        {
            FastLED.addLeds<NEOPIXEL, PIN>(segment.getLeds(), segment.size());
        }

        FastLED.clear(true);
        FastLED.setMaxPowerInVoltsAndMilliamps(voltage.toBase(), amperage.toMilli());
        Serial.println("LED setup complete.");
    }

    void setAllTo(Color color)
    {
        char buffer[50]; // Buffer to hold the formatted string
        sprintf(buffer, "Setting all pixels to R: %u, G: %u, B: %u", color.red, color.green, color.blue);
        Serial.println(buffer);

        for (auto &segment : segments)
        {
            segment.setAllTo(color);
        }

        FastLED.show();
    }
};
