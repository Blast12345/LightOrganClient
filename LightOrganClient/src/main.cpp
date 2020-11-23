// Imports
#include "FastLED.h"

//LED Configuration
const unsigned int LED_COUNT = 12;
const int LED_PIN = 13;

//State
CRGB leds[LED_COUNT];

// Setup
void setup()
{
  // Basic setup
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);            // Suggested wait to reduce issues with WiFi. Not sure if needed

  // Setup neopixel strand
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
}

// Loop
void loop()
{
  leds[0].setRGB(128, 128, 128);
  FastLED.show();
}
