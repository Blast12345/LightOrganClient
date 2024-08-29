#include "Configuration.h"
#include "LedManager.h"
#include "FastLED.h"

CRGB leds[ledCount];

void LedManager::setup()
{
    FastLED.addLeds<NEOPIXEL, ledPin>(leds, ledCount);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 14000);
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

CRGB ColorFromWheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void LedManager::useFallbackLoop()
{
    int rotations = 1;
    int rotationDelay = 5;       // Delay in milliseconds to control speed
    byte startingColorIndex = 0; // Starting color index for the color wheel

    for (int rotation = 0; rotation < rotations * 256; rotation++)
    { // Multiply by 256 for a smooth transition
        for (uint i = 0; i < ledCount; i++)
        {
            // Calculate color offset for each LED to create the color wheel effect
            byte colorIndex = (i * 256 / ledCount + startingColorIndex) & 255;
            leds[i] = ColorFromWheel(colorIndex);
        }

        // for (uint i = 60; i < 120; i++)
        // {
        //     // Calculate color offset for each LED to create the color wheel effect
        //     byte colorIndex = (i * 256 / 60 + startingColorIndex) & 255;
        //     leds[i] = ColorFromWheel(colorIndex);
        // }

        FastLED.show();
        startingColorIndex++; // Move to the next color in the wheel
        delay(rotationDelay);
    }
}