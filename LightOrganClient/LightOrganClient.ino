// WiFi
#include <ESP8266WiFi.h>

//Sockets
#include <WebSocketsServer.h>
#include <WebSocketsClient.h>
#include <WebSockets.h>
#include <SocketIOclient.h>

//https://tttapa.github.io/ESP8266/Chap14%20-%20WebSocket.html

const char* ssid     = "LightOrgan";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "thecolorofmusic";     // The password of the Wi-Fi network
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  Serial.println("WEBSOCKET EVENT");
}



void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  // server address, port and URL
  webSocket.begin("192.168.4.1", 9999, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);
  
  // start heartbeat (optional)
  // ping server every 15000 ms
  // expect pong from server within 3000 ms
  // consider connection disconnected if pong is not received 2 times
  webSocket.enableHeartbeat(15000, 3000, 2);
  
}

void loop() { 
  webSocket.loop();
}
