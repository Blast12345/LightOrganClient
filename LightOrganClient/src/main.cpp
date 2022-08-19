#include "FastLED.h"
#include "WifiManager.h"
#include "SocketManager.h"
#include "CommandParser.h"
#include "Configuration.h"

// State
WifiManager wifiManager;
SocketManager socketManager;
CRGB leds[ledCount];

// Setup
void configureSerialOutput()
{
  Serial.begin(115200);
}

void warmupForWifi()
{
  // NOTE: Connecting to wifi immediately resulted in messages not being received.
  delay(10);
}

void connectToWifi()
{
  wifiManager.connect(ssid, password);
}

void connectToSocket()
{
  socketManager.connectToSocket(port);
}

void configureNeopixels()
{
  FastLED.addLeds<NEOPIXEL, ledPin>(leds, ledCount);
}

void setup()
{

  configureSerialOutput();
  warmupForWifi();
  connectToWifi();
  connectToSocket();
  configureNeopixels();
}

// Loop
void reconnectToWifiIfNeeded()
{
  wifiManager.connectIfNeeded(ssid, password);
}

void setAllLedsToColor(uint32_t color)
{
  Serial.println("Setting pixels...");

  for (uint i = 0; i < ledCount; i++)
  {
    leds[i].setColorCode(color);
  }

  FastLED.show();
}

void loop()
{
  reconnectToWifiIfNeeded();
  socketManager.getNextColor();
  // setAllLedsToColor();
}