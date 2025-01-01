#include <Arduino.h>
#include "Sensors.h"
#include "Actuators.h"
#include "Network.h"

#include <WiFi.h>
#include <PubSubClient.h>

// Configuration MQTT
const char* mqtt_server = "192.168.1.178"; // Adresse IP de votre broker MQTT
const int mqtt_port = 1883;               // Port MQTT (par défaut : 1883)
const char* mqtt_topic = "/test/topic";   // Sujet utilisé pour les messages

WiFiClient espClient;
PubSubClient client(espClient);

// Fonction pour publier une donnée sur un topic MQTT
void sendData(const char* topic, const char* payload) {
    if (!client.connected()) {
        reconnect();
    }
    client.loop(); // Gestion des tâches MQTT

    // Envoi du message
    if (client.publish(topic, payload)) {
        Serial.println("Message envoyé avec succès !");
        Serial.print("Topic : ");
        Serial.println(topic);
        Serial.print("Payload : ");
        Serial.println(payload);
    } else {
        Serial.println("Échec de l'envoi du message.");
    }
}

// Callback pour recevoir les messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message reçu sur le sujet : ");
  Serial.println(topic);

  Serial.print("Contenu : ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Connexion au broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion au broker MQTT...");
    if (client.connect("ESP32Client")) { // Nom du client
      Serial.println("Connecté !");
      client.subscribe(mqtt_topic);      // Souscription au sujet
    } else {
      Serial.print("Echec, rc=");
      Serial.print(client.state());
      Serial.println(" Nouvelle tentative dans 5 secondes...");
      delay(5000);
    }
  }
}

void setup(void)
{
  //Set the baudrate to 115200
  Serial.begin(115200);

  //Pump init
  pump_init();

  //network init
  network_setup();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop(void)
{
  //Measure Humidity with Sensors
  sensor_data_acquisition();

  //Com MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // MQTT msg post
  static unsigned long lastMsg = 0;
  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    String message = "Hello, MQTT!";
    Serial.print("Envoi du message : ");
    Serial.println(message);
    client.publish(mqtt_topic, message.c_str());
  }

  //TO DO Grafana with influxdb to visualize datas on a dashboard

  sendData("esp32/test", "Ceci est un message test");
  delay(5000)

  //Irrigation
  pump_irrigation_automation();
}