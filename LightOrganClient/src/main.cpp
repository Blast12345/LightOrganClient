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
const int LED_COUNT = 300;
const int LED_PIN = 13;

//State
SocketManager socketManager;
Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Setup
void setup()
{
  // Basic setup
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);            // Suggested wait to reduce issues with WiFi. Not sure if needed

  // Setup neopixel strand
  strand.begin();
  strand.clear();
}

// Loop
void loop()
{
  // If WiFi is disconnected, attempt to connect
  if (WifiManager::isConnected() == false)
  {
    WifiManager::connect(ssid, password);
    return;
  }

  // If socket is disconnected, attempt to connect
  if (socketManager.isConnected() == false)
  {
    socketManager.connectToSocket(serverIP, port);
    socketManager.sendLedCount(LED_COUNT);
    return;
  }

  //If connected to the socket, then attempt to retrieve the next command and update the
  std::vector<RGB> colors = socketManager.getNextCommand();

  //TODO: Create NeopixelManager?
  for (uint i = 0; i < colors.size(); i++)
  {
    RGB color = colors[i];

    int r = color.red;
    int g = color.green;
    int b = color.blue;

    strand.setPixelColor(i, strand.Color(r, g, b));
  }

  Serial.println("Setting pixels...");
  strand.show();
}
