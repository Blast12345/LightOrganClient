#include "ColorParser.h"
#include "Configuration.h"
#include "FastLED.h"
#include "SocketManager.h"
#include "WifiManager.h"
#include "LedManager.h"

// State
LedManager ledManager;
WifiManager wifiManager;
SocketManager socketManager;
ColorParser colorParser;
bool isNewConnection = true;

// Setup
void configureSerialOutput()
{
  Serial.begin(115200);
}

void warmUpWifi()
{
  // NOTE: Connecting to wifi immediately resulted in messages not being received.
  uint32_t tenMs = 10;
  delay(tenMs);
}

void setup()
{
  configureSerialOutput();
  ledManager.setup();
  warmUpWifi();
}

// Loop
void connectToWifi()
{
  wifiManager.connect(ssid, password);
}

void handleInitialConnectionIfNeeded()
{
  if (isNewConnection)
  {
    // wifiManager.printConnectionInformation();
    socketManager.openPort(port);
    // isNewConnection = false;
  }
}

void setLedsToNextColor()
{
  std::string colorString = socketManager.getNextString();
  Color color = colorParser.getColor(colorString);
  ledManager.setAllTo(color);
}

void loop()
{
  wifiManager.printConnectionInformation();

  if (wifiManager.isDisconnected())
  {
    isNewConnection = true;
    connectToWifi();

    while (wifiManager.isDisconnected())
    {
      Serial.println("Waiting for connection...");
      delay(1);
    }
  }
  // else if (!wifiManager.isReliableConnection())
  // {
  //   // ledManager.useFallbackLoop();
  // }
  else if (wifiManager.isConnected())
  {
    handleInitialConnectionIfNeeded();
    // setLedsToNextColor();
  }
}