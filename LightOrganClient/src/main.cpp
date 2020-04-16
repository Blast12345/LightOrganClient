// Imports
#include "WifiManager.h"
#include "SocketManager.h"

// Configuration
const char *ssid = "LightOrgan";          // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "thecolorofmusic"; // The password of the Wi-Fi network
const char *serverIP = "192.168.4.1";     // The IP address of the Raspberry Pi //TODO: Improve this comment
const int port = 9999;                    // The port of the socket we want to connect to

//State
SocketManager socketManager;

// Setup
void setup()
{
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);            // Suggested wait to reduce issues with WiFi. Not sure if needed

  WifiManager::connect(ssid, password);

  socketManager.connectToSocket(serverIP, port);
}

// Loop
void loop()
{
    // while (socketManager.client.connected() || socketManager.client.available())
    // {
    //     if (socketManager.client.available())
    //     {
    //         String line = socketManager.client.readStringUntil('\n');
    //         Serial.println(line);
    //     }
    // }
  String next = socketManager.getNextCommand();
  Serial.println(next);
}