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
  attemptToConnect(ssid, password);
  printConnectionInformation();
}

void WifiManager::wakeWifiHardware()
{
  WiFi.setSleep(false);
}

void WifiManager::attemptToConnect(const char *ssid, const char *password)
{
  WiFi.begin(ssid, password);
}

void WifiManager::printConnectionInformation()
{
  printSSID();
  printSignalStrength();
  printIpAddress();
}

void WifiManager::printSSID()
{
  Serial.println("SSID: " + WiFi.SSID());
}

void WifiManager::printSignalStrength()
{
  Serial.println("Signal strength: " + String(WiFi.RSSI()) + " dBm");
}

void WifiManager::printIpAddress()
{
  Serial.println("IP address: " + WiFi.localIP().toString());
}