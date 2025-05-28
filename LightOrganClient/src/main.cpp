#include "Configuration.h"
#include "LOServer.h"
#include "Network.h"
#include "helpers/Wait.h"

Network network(networkCredentials);
LOServer server(serverPort);

void setup()
{
  Serial.begin(baudRate);
  waitOneSecond(); // Give the device some time to warm up or weird things tend to happen.

  Serial.println("Baud rate set to: " + String(baudRate));

  ledChain.setup();

  Serial.println("Setup complete.");
}

// cppcheck-suppress unusedFunction
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