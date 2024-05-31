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

void updateLedsUsingFallback()
{
  for (int colorStep = 0; colorStep < 256; colorStep++)
  {
    Color color;
    color.red = sin(colorStep * 0.024) * 127 + 128;
    color.green = sin(colorStep * 0.024 + 2 * PI / 3) * 127 + 128;
    color.blue = sin(colorStep * 0.024 + 4 * PI / 3) * 127 + 128;

    ledManager.setAllTo(color);

    delay(10); // delay for visual effect, adjust as needed
  }
}

void handleInitialConnectionIfNeeded()
{
  wifiManager.printConnectionInformation();
  socketManager.openPort(port);
  // TODO: new connection false?
}

void setLedsToNextColor()
{
  std::string colorString = socketManager.getNextString();
  Color color = colorParser.getColor(colorString);
  ledManager.setAllTo(color);
}

void loop()
{
  if (wifiManager.isDisconnected())
  {
    connectToWifi();
    updateLedsUsingFallback();
    isNewConnection = true;
  }
  else if (wifiManager.isConnected())
  {
    handleInitialConnectionIfNeeded();
    setLedsToNextColor();
    isNewConnection = false;
  }
}