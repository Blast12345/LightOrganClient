#include "Configuration.h"
#include "Secrets.h"

Network network(networkSSID, networkPassword);

// Server
IPAddress serverIP(192, 168, 1, 82);
int serverPort = 9999;
LOServer server(serverPort);