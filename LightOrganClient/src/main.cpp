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

void setup()
{
  delay(1000); // Give the device some time to warm up or weird things tend to happen.
  Serial.begin(buadRate);
  Serial.println("Buad rate set.");
  ledManager.setup();
  Serial.println("Setup complete.");
}

// Loop
void handleInitialConnectionIfNeeded()
{
  if (isNewConnection)
  {
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
  if (wifiManager.isDisconnected())
  {
    //   isNewConnection = true;
    wifiManager.connect(ssid, password);
  }
  else if (wifiManager.isConnected())
  {
    // handleInitialConnectionIfNeeded();
    // setLedsToNextColor();
  }
}