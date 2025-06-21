#include "Configuration.h"
#include "helpers/Wait.h"
#include "networking/LOServer.h"
#include "networking/Network.h"
#include <esp_wifi.h>

#include <esp_now.h>
#include <queue>

Network network(networkCredentials);
LOServer server(serverPort);

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  Serial.println("Received");

  // Convert incoming data to a String
  String receivedData = String((char *)incomingData).substring(0, len);

  // Print the received data
  Serial.println("Data Received: " + receivedData);
}

void setup()
{
  Serial.begin(baudRate);
  waitOneSecond(); // Give the device some time to warm up or weird things tend to happen.

  Serial.println("Baud rate set to: " + String(baudRate));

  // ledChain.setup();

  Serial.println("Setup complete.");

  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else
  {
    Serial.println("ESP-NOW initialized successfully");
  }

  if (esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv)) != ESP_OK)
  {
    Serial.println("Error registering ESP-NOW receive callback");
  }
  else
  {
    Serial.println("ESP-NOW receive callback registered successfully");
  }
}

// cppcheck-suppress unusedFunction
void loop()
{
  // waitOneSecond(); // Give the device some time to warm up or weird things tend to happen.
  // Serial.println("Looping...");
  // if (network.isDisconnected())
  // {
  //   network.connect();
  //   waitOneSecond(); // Give the device time to be assigned an IP and whatnot.
  //   network.printConnectionInformation();
  // }

  // if (network.isConnected() && server.isNotListening())
  // {
  //   try
  //   {
  //     server.beginListening();
  //   }
  //   catch (const std::runtime_error &e)
  //   {
  //     Serial.println("Error: " + String(e.what()));
  //     waitOneSecond();
  //   }
  // }

  // if (network.isConnected() && server.isListening())
  // {
  //   server.onNextColor([](Color color)
  //                      { ledChain.setAllTo(color); });
  // }
}