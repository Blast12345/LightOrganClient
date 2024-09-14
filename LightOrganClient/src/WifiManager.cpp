#include "WifiManager.h"

boolean WifiManager::isConnected()
{
  return WiFi.isConnected() == true;
}

boolean WifiManager::isDisconnected()
{
  return WiFi.isConnected() == false;
}

boolean WifiManager::isReliableConnection()
{
  return WiFi.RSSI() > -80 && WiFi.localIP().toString() != "0.0.0.0";
}

void WifiManager::connect(const char *ssid, const char *password)
{
  wakeWifiHardware();

  while (isDisconnected())
  {
    Serial.println("Attempting to connect to WiFi...");
    attemptToConnect(ssid, password);
  }
}

void WifiManager::wakeWifiHardware()
{
  WiFi.setSleep(false);
}

void WifiManager::attemptToConnect(const char *ssid, const char *password)
{
  WiFi.begin(ssid, password);
  delay(100);

  if (isConnected())
  {
    printConnectionInformation();
  }
}

void WifiManager::printConnectionInformation()
{
  Serial.println("Connection established.");
  Serial.println("SSID: " + WiFi.SSID());
  Serial.println("Signal strength: " + String(WiFi.RSSI()) + " dBm");
  Serial.println("IP address: " + WiFi.localIP().toString());
}