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

  if (next.isValid() == false)
  {
    // If a number is -1, then we are missing some data and we should exit this step in the loop.
    return;
  }

  for (int i = 0; i < LED_TOTAL; i++)
  {
    int r = next.red;
    int g = next.green;
    int b = next.blue;
    strand.setPixelColor(i, strand.Color(r, g, b));
    Serial.println();
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.print(b);
    Serial.println();
  }

  strand.show();
}
