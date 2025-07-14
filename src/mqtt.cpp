#include "mqtt.h"

uint32_t lastSendTime = 0;

WiFiClient espClient;
PubSubClient client(espClient);

String mqtt_command_topic = "/esp32/command";

// MQTT Callback
void callbackMQTT(char* topic, byte* payload, unsigned int length) 
{
  payload[length] = '\0';  // be sure that string is finished
  String message = String((char*)payload);

  Serial.print("Message received on [");
  Serial.print(topic);
  Serial.print("] : ");
  Serial.println(message);

  if (String(topic) == mqtt_command_topic) {
    Serial.println("Command to process (not implemented yet)");
  }
}

// MQTT Reconnect
void reconnectMQTT()
{
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker...");

    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT Broker !");
      
      if(client.subscribe(mqtt_command_topic.c_str())){
        Serial.println("Correctly Reconnected");
      }
    } else {
      Serial.println("Échec, code erreur = ");
      Serial.print(client.state());
      Serial.println(". Nouvel essai dans 5 secondes.");
      delay(5000);
    }
  }
}

// MQTT Publish Data on topic
void publishMQTT(const SIS_Config* cfg, const char* data, int i) 
{
    JsonDocument doc;

    switch (cfg->sensor_list[i]->getType()){
    case SENSOR_NONE:
      break;
    case SENSOR_MOISTURE:
      doc["moisture"] = data;
      break;
    case SENSOR_HUMIDITY:
      doc["humidity"] = data;
      break;
    case SENSOR_TEMPERATURE:
      doc["temperature"] = data;
      break;
    }

    char buffer[100];
    serializeJson(doc, buffer);

    if (client.publish(cfg->mqtt_data_topic.c_str(), buffer)) {
      Serial.println("Data Posted :");
      Serial.println(buffer);
    } else {
      Serial.println("Post Failure.");
    }
}

// MQTT Setup
void setupMQTT(SIS_Config* cfg) 
{
  Serial.println(" MQTT Broker : ");
  Serial.println(cfg->mqtt_broker.c_str());
  client.setServer(cfg->mqtt_broker.c_str(), cfg->mqtt_port);
  client.setCallback(callbackMQTT);
}

// MQTT Loop
void processMQTT(SIS_Config *cfg, const char* data, int i)
{
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();
  publishMQTT(cfg, data, i);
}