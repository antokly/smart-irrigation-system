#include "wifi.h"

// WIFI SETUP (On the Client)
void wifi_setup() {
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