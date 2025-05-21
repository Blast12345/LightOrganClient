#include "Configuration.h"
#include "helpers/Wait.h"
#include "Network.h"
#include "LOServer.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
Network network(networkCredentials);
LOServer server(serverPort);
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

void setup()
{
  Serial.begin(baudRate);
  waitOneSecond(); // Give the device some time to warm up or weird things tend to happen.

  Serial.println("Baud rate set to: " + String(baudRate));

  ledChain.setup();

  Serial.println("Setup complete.");
}

void loop()
{
  if (network.isDisconnected())
  {
    network.connect();
    waitOneSecond(); // Give the device time to be assigned an IP and whatnot.
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
      waitOneSecond();
    }
  }

  if (network.isConnected() && server.isListening())
  {
    server.onNextColor([](Color color)
                       { ledChain.setAllTo(color); });
  }
}
