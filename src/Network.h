#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <WiFi.h>
#include <string.h>
#include "SendHTTPWebServer.h"

extern WiFiServer server;
extern const char* ssid;
extern const char* password;

void network_setup();

void setup_wifi();
void setup_server();

#endif