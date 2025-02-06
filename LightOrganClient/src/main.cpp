#include "ColorParser.h"
#include "Configuration.h"
#include "FastLED.h"
#include "SocketManager.h"
#include "LedManager.h"

LedManager ledManager; // TODO: Better name?

void setup()
{
  delay(1000); // Give the device some time to warm up or weird things tend to happen.

  Serial.begin(baudRate);
  Serial.println("Baud rate set to: " + String(baudRate));

  ledManager.setup();

  Serial.println("Setup complete.");
}

// TODO: State machine?
void loop()
{
  if (network.isDisconnected())
  {
    network.connect();
    server.reset();
  }

  if (network.isConnected() && server.isDisconnected())
  {
    server.connect();
  }

  if (network.isConnected() && server.isConnected())
  {
    Color nextColor = server.getNextColor();
    ledManager.setAllTo(nextColor);
  }
}