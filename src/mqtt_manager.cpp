#include "mqtt_manager.h"

WiFiClient espClient; // Connection layer
PubSubClient client(espClient); // Protocol layers


void mqtt_setup(void)
{
    client.setServer(mqtt_server, mqtt_port);
    //client.setCallback(callback);
}

// MQTT message posting on topic
void mqtt_send_data(const char* topic, const char* payload) {

    //  MQTT broker connection
    if (!client.connected()) {
        reconnect();
    }

    client.loop(); // Handle MQTT tasks

    // Send the message
    if (client.publish(topic, payload)) {
        // Serial.println("Message sent successfully!");
        // Serial.print("Topic: ");
        // Serial.println(topic);
        // Serial.print("Payload: ");
        // Serial.println(payload);
    } else {
        Serial.println("Failed to send message.");
    }
}

// Callback function to receive messages
// void callback(char* topic, byte* payload, unsigned int length) {
//   Serial.print("Message received on topic: ");
//   Serial.println(topic);

//   Serial.print("Content: ");
//   for (int i = 0; i < length; i++) {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();
// }

// Connect to the MQTT broker
void reconnect() {

  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker...");
    
    if (client.connect("ESP32Client")) {  // Client name
      Serial.println("Connected!");
      client.subscribe(mqtt_topic);       // Subscribe to the topic
    } else {
      Serial.print("Connection failed, rc=");
      Serial.print(client.state());
      Serial.println(". Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
