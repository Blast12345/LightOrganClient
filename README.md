# Setup

A configuration file is needed.
Create the file `./LightOrganClient/src/Configuration.h`
Add the following information to `Configuration.h`:
```
const char *ssid = "your access point";
const char *password = "your access point password;
const char *serverIP = "your server ip";
const int port = 9999;
const int ledCount = 300;
const int ledPin = 13;
```
