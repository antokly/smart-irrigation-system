#include "mqtt_manager.h"
#include "sensor.h"

// Connection layer
WiFiClient espClient;
// Protocol layers
PubSubClient client(espClient);

uint32_t lastSendTime = 0;
uint32_t lastMessageTime = 0;

// MQTT Init
void mqtt_setup(void)
{
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// MQTT Process 
void mqtt_loop(const String data)
{
  if (!client.connected()) {
      reconnect();
  }

  // MQTT Send Data
  if (millis() - lastSendTime >= sendDataInterval) {
    mqtt_send_data(mqtt_send_topic, data.c_str()); // Convert String to C-string
    lastSendTime = millis();
  }
}

// MQTT message posting on topic
void mqtt_send_data(const char* topic, const char* data)
{
    //  MQTT broker connection
    if (!client.connected()) {
        reconnect();
    }

    client.loop(); // Handle MQTT tasks

    // Send the message
    if (client.publish(topic, data)) {
#ifdef COM_LOG_ENABLE
        Serial.println("Message sent successfully!");
        Serial.print("Topic: ");
        Serial.println(topic);
        Serial.print("Payload: ");
        Serial.println(data);
#endif
    } else {
        Serial.println("Failed to send message.");
    }
}

// Callback function to receive MQTT commands
void callback(char* topic, byte* payload, unsigned int length)
{
  if (String(topic) == mqtt_reception_topic) { // Check the topic
        unsigned long now = millis();
        if (now - lastMessageTime < receptionInterval) {
            return; // Ignore messages that are too frequent
        }
        lastMessageTime = now;
#ifdef COM_LOG_ENABLE
        Serial.print("Message received on ");
        Serial.print(topic);
        Serial.print(" : ");
        for (int i = 0; i < length; i++) {
            Serial.print((char)payload[i]);
        }
        Serial.println();
#endif
  }
}

// Connect to the MQTT broker and subscribe to the mqtt reception topic
void reconnect()
{
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker...");
    
    if (client.connect("ESP32Client")) {  // Client name
      Serial.println("Connected!");
      client.subscribe(mqtt_reception_topic);       // Subscribe to the topic
    } else {
      Serial.print("Connection failed, rc=");
      Serial.print(client.state());
      Serial.println(". Retrying in 5 seconds...");
      delay(5000);
    }
  }
}