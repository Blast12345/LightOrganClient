#pragma once

#include "Color.h"
#include "Configuration.h"
#include <FastLED.h>
#include <vector>

class LedSegment
{
private:
    std::vector<CRGB> leds;

public:
    explicit LedSegment(unsigned int count) : leds(count, CRGB::Black) {}

    auto getLeds() -> CRGB *
    {
        return leds.data();
    }

    auto size() const -> unsigned int
    {
        return leds.size();
    }

    void setAllTo(const Color &color)
    {
        for (auto &led : leds)
        {
            led.setRGB(color.red, color.green, color.blue);
        }
    }
};
