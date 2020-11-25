// Imports
#include "FastLED.h"
#include "WifiManager.h"
#include "SocketManager.h"
#include "CommandParser.h"

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
CRGB leds[LED_COUNT];

// Setup
void setup()
{
  // Basic setup
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(10);            // Suggested wait to reduce issues with WiFi. Not sure if needed

  // Setup neopixel strand
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
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

  // If connected to the socket, then attempt to retrieve the next command
  std::string command = socketManager.getNextCommand();

  // Turn our command string into hex codes
  std::vector<uint32_t> colors = CommandParser::parseCommand(command);

  // Deploy our colors to the neopixels
  Serial.println("Setting pixels...");

  for (uint i = 0; i < colors.size(); i++)
  {
    uint32_t color = colors[i];
    leds[i].setColorCode(color);
  }

  FastLED.show();
}
