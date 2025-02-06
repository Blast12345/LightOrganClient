#include "Configuration.h"

char *networkSSID = "DasHouse";
char *networkPassword = "DyehtsoDPtW?Itn.Inastjwty.";
Network network(networkSSID, networkPassword);

// Server
IPAddress serverIP(192, 168, 1, 82);
int serverPort = 9999;
LOServer server(serverPort);