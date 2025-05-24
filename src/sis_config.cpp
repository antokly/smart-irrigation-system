#include "sis_config.h"

/**
 * Configuration Steps Before Running the Program on the Target Device:
 *
 * 1. **Configure Network Settings**  
 *    - Set the SSID and password for your local Wi-Fi access point in the network configuration fields.
 *
 * 2. **Verify MQTT Broker Status**  
 *    - Ensure your MQTT broker (Mosquitto) is running by executing:  
 *      `sudo systemctl status mosquitto`
 *    - If the broker is inactive, restart it and disable the firewall if necessary:  
 *      `sudo ufw disable && sudo systemctl restart mosquitto`
 *
 * 3. **Set Broker IP Address**  
 *    - Find your machine’s IP address using:  
 *      `hostname -I`  
 *    - Copy the IP address and paste it into the project’s configuration for the MQTT broker.
 *
 * 4. **Subscribe to Sensor Data**  
 *    - Monitor sensor data published to the MQTT topic by subscribing with:  
 *      `mosquitto_sub -h <broker-ip> -t "/sending/topic"`  
 *      *(Replace `<broker-ip>` with the actual IP address of your broker, or use `localhost` if running locally.)*
 *          **(Use 'localhost' if the broker is running on the same device)
 */

// Network Settings
const char* ssid = "";
const char* password = "";

// Measure Config
const uint32_t readingMeasurePeriod = 3000;         // 3 sec
const int samplesByMeasure = 25;                    // samples number by measure for moving average => Reduce noise on measures
                                                    // (" moyennage glissant ") // Compromis Precision / Conso

// MQTT Configs
const char* mqtt_server = "";               // IP of MQTT Broker
const int mqtt_port = 1883;                             // MQTT Port (By default : 1883)
const char* mqtt_send_topic = "/sending/topic";
const char* mqtt_reception_topic = "/reception/topic";
const uint32_t sendDataInterval = 10000;                // 10 sec
const uint32_t receptionInterval = 500;                 // Check MQTT reception every 0.5 sec