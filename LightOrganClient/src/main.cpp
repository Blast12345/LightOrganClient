#include "ColorParser.h"
#include "CommandParser.h"
#include "Configuration.h"
#include "FastLED.h"
#include "OrganColor.h"
#include "SocketManager.h"
#include "WifiManager.h"

// State
WifiManager wifiManager;
SocketManager socketManager;
ColorParser colorParser;
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

void reconnectToSocketIfNeeded() {
  // TODO:
  connectToSocket();
}

void setLedsForNextColor() 
{
  std::string colorString = socketManager.getNextString();
  OrganColor color = colorParser.getColor(colorString);
  setAllLedsToColor(color);
}

// TODO: Perhaps this could be moved to a LedManager?
void setAllLedsToColor(OrganColor color)
{
  Serial.println("Setting pixels...");

  for (uint i = 0; i < ledCount; i++)
  {
    leds[i].setRGB(color.red, color.green, color.blue);
  }

  FastLED.show();
}

void loop()
{
  reconnectToWifiIfNeeded();
  reconnectToSocketIfNeeded();
  setLedsForNextColor();
}