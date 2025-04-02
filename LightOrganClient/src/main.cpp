#include "Configuration.h"
#include "Leds.h"
#include "Secrets.h"
#include "Network.h"
#include "LOServer.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
Leds leds;
Network network(networkSSID, networkPassword);
LOServer server(serverPort);
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

void setup()
{
  Serial.begin(baudRate);
  delay(1000); // Give the device some time to warm up or weird things tend to happen.

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
    delay(1000); // Give the device time to be assigned an IP and whatnot.
    network.printConnectionInformation();
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
