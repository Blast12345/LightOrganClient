#include "Leds.h"
#include "FastLED.h"
#include "Configuration.h"

CRGB leds[ledCount];

void Leds::setup()
{
    FastLED.addLeds<NEOPIXEL, ledPin>(leds, ledCount);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 2400);
}

void Leds::setAllTo(Color color)
{
    Serial.println("Setting pixels...");

    for (uint i = 0; i < ledCount; i++)
    {
        leds[i].setRGB(color.red, color.green, color.blue);
    }

    FastLED.show();
}