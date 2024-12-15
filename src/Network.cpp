#include "Network.h"

//Network Settings
const char* ssid = "";
const char* password = "";
HTTPClient httpclient;
WiFiServer server(80);

// Network Setup
void network_setup() {
    setup_wifi();
    setup_server();
}

// WIFI SETUP (On the Client)
void setup_wifi() {
    Serial.println("Setting up WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    unsigned long startTime = millis();
    const unsigned long timeout = 10000; // Timeout in ms

    //Wait until wifi connected
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");

        if (millis() - startTime > timeout) {
            Serial.println("\nFailed to connect to WiFi: Timeout reached!");
            return; // Sortir ou effectuer une autre action
        }
    }

    Serial.println("\nWiFi connected!");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("WiFi Setup Done!\n");
}

// SERVER SETUP
void setup_server() {
    Serial.println("Setting up server...");
    server.begin();
    Serial.println("Server is up and running!\n");
}