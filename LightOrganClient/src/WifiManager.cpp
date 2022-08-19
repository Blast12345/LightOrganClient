#include "WifiManager.h"

void WifiManager::connectIfNeeded(const char *ssid, const char *password)
{
  if (isConnected() == false)
  {
    connect(ssid, password);
    return;
  }
}

boolean WifiManager::isConnected()
{
  return WiFi.isConnected();
}

void WifiManager::connect(const char *ssid, const char *password)
{
  startWifiConnection(ssid, password);
  printConnectingMessage(ssid);
  waitForWifiConnection();
  printConnectedMessage();
}

void WifiManager::startWifiConnection(const char *ssid, const char *password)
{
  WiFi.begin(ssid, password);
}

void WifiManager::printConnectingMessage(const char *ssid)
{
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");
}

void WifiManager::waitForWifiConnection()
{
  int timeAwaited = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    printTimeAwaited(timeAwaited);
    timeAwaited++;
  }

  Serial.println('\n');
}

void WifiManager::printTimeAwaited(int timeAwaited)
{
  Serial.print(timeAwaited);
  Serial.print(' ');
}

void WifiManager::printConnectedMessage()
{
  Serial.println("Connection established!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer
}