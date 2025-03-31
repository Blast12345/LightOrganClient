#include "Configuration.h"
#include "Leds.h"

Leds leds;

void setup()
{
  delay(1000); // Give the device some time to warm up or weird things tend to happen.

  Serial.begin(baudRate);
  Serial.println("Baud rate set to: " + String(baudRate));

  leds.setup();

  Serial.println("Setup complete.");
}

// cppcheck-suppress unusedFunction ; This function is called by the Arduino framework.
void loop()
{
  if (network.isDisconnected())
  {
    network.connect();
  }

  if (network.isConnected() && server.isNotListening())
  {
    try
    {
      server.beginListening();
    }
    catch (const std::runtime_error &e)
    {
      Serial.println("Error: " + String(e.what()));
      delay(1000);
    }
  }

  if (network.isConnected() && server.isListening())
  {
    server.onNextColor([](Color color)
                       { leds.setAllTo(color); });
  }
}