#include "ColorParser.h"
#include "Configuration.h"
#include "FastLED.h"
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
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2400);
}

// TODO: Perhaps this could be moved to a LedManager?
void setAllLedsToColor(Color color)
{
  Serial.println("Setting pixels...");

  for (uint i = 0; i < ledCount; i++)
  {
    leds[i].setRGB(color.red, color.green, color.blue);
  }

  FastLED.show();
}

void loopThroughColorWheel()
{
  for (int colorStep = 0; colorStep < 256; colorStep++)
  {
    Color color;
    color.red = sin(colorStep * 0.024) * 127 + 128;
    color.green = sin(colorStep * 0.024 + 2 * PI / 3) * 127 + 128;
    color.blue = sin(colorStep * 0.024 + 4 * PI / 3) * 127 + 128;

    setAllLedsToColor(color);

    delay(10); // delay for visual effect, adjust as needed
  }

  loopThroughColorWheel();
}

void setup()
{
  // configureSerialOutput();
  // warmupForWifi();
  // connectToWifi();
  // connectToSocket();
  configureNeopixels();
  loopThroughColorWheel();
}

// Loop
void reconnectToWifiIfNeeded()
{
  wifiManager.connectIfNeeded(ssid, password);
}

void reconnectToSocketIfNeeded()
{
  // TODO:
  connectToSocket();
}

void setLedsForNextColor()
{
  std::string colorString = socketManager.getNextString();
  Color color = colorParser.getColor(colorString);
  setAllLedsToColor(color);
}

void loop()
{
  reconnectToWifiIfNeeded();
  reconnectToSocketIfNeeded();
  setLedsForNextColor();
}