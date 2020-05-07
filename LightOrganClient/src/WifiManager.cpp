#include "WifiManager.h"

void WifiManager::connect(const char *ssid, const char *password)
{
    //Attempt to connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ...");

    //Wait for the WiFi to connect
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(++i);
        Serial.print(' ');
    }

    //Succesful Connection
    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer
}

boolean WifiManager::isConnected() 
{
    return WiFi.isConnected();
}