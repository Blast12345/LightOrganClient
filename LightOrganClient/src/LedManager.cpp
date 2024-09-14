#include "Configuration.h"
#include "LedManager.h"
#include "FastLED.h"

CRGB leds[ledCount];

void LedManager::setup()
{
    FastLED.addLeds<NEOPIXEL, ledPin>(leds, ledCount);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 14000);
    Serial.println("LED setup complete.");
}

void LedManager::setAllTo(Color color)
{
    char buffer[50]; // Buffer to hold the formatted string
    sprintf(buffer, "Setting pixels to R: %u, G: %u, B: %u", color.red, color.green, color.blue);
    Serial.println(buffer);

    for (uint i = 0; i < ledCount; i++)
    {
        leds[i].setRGB(color.red, color.green, color.blue);
    }

    FastLED.show();
}
