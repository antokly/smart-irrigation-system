#include "wifi.h"

/* Wifi setup */
void setupWifi(SIS_Config *cfg)
{
    Serial.println("Setting up WiFi...");
    WiFi.mode(WIFI_STA);
    Serial.print("SSID: ");
    Serial.println(cfg->wifi_ssid);
    Serial.print("Password: ");
    Serial.println(cfg->wifi_pwd);
    WiFi.begin(cfg->wifi_ssid.c_str(), cfg->wifi_pwd.c_str());

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
    Serial.println(cfg->wifi_ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("WiFi Setup Done!\n");
}