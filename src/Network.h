#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h>

extern WiFiServer server;

void network_setup();
void setup_wifi();
void setup_server();

#endif