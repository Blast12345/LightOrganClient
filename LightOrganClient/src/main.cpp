#include "FastLED.h"
#include "WifiManager.h"
#include "SocketManager.h"
#include "CommandParser.h"

// Configuration
const char *ssid = "-";     // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "-"; // The password of the Wi-Fi network
const char *serverIP = "-"; // The IP address of the Raspberry Pi //TODO: Improve this comment
const int port = 9999;      // The port of the socket we want to connect to
const int LED_COUNT = 300;
const int LED_PIN = 13;

// State
WifiManager wifiManager;
SocketManager socketManager;
CRGB leds[LED_COUNT];

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
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
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

  for (uint i = 0; i < colors.size(); i++)
  {
    uint32_t color = colors[i];
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