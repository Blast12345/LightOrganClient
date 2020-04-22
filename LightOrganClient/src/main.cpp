// Imports
#include <Adafruit_NeoPixel.h>
#include "WifiManager.h"
#include "SocketManager.h"

// WiFi Configuration
const char *ssid = "LightOrgan";          // The SSID (name) of the Wi-Fi network you want to connect to
const char *password = "thecolorofmusic"; // The password of the Wi-Fi network
const char *serverIP = "192.168.4.1";     // The IP address of the Raspberry Pi //TODO: Improve this comment
const int port = 9999;                    // The port of the socket we want to connect to

//LED Configuration
const int LED_TOTAL = 300;
const int LED_PIN = 13;

//State
SocketManager socketManager;
Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_TOTAL, LED_PIN, NEO_GRB + NEO_KHZ800);

// Setup
void setup()
{
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);            // Suggested wait to reduce issues with WiFi. Not sure if needed

  WifiManager::connect(ssid, password);

  socketManager.connectToSocket(serverIP, port);

  strand.begin();
  strand.clear();
}

// Loop
void loop()
{
  //TODO: Implement reconnect

  RGB next = socketManager.getNextCommand();

  //TODO: MOVE THIS TO LED MANAGER
  if (next.isValid() == false)
  {
    return;
  }

  int r = next.red;
  int g = next.green;
  int b = next.blue;

  for (int i = 0; i < LED_TOTAL; i++)
  {
    strand.setPixelColor(i, strand.Color(r, g, b));
  }

  strand.show();
}
