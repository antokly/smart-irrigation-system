/**
 * Project Configs Manager to store or load configs from NVS OR JSON config file
 */

#include "config_manager.h"

Preferences preferences;

/**
 * Set System Configs from Default Config
 */
bool setDefaultConfig(SIS_Config *cfg)
{

  cfg->wifi_ssid = WIFI_SSID;
  cfg->wifi_pwd = WIFI_PASSWORD;

  cfg->mqtt_broker = MQTT_BROKER;
  cfg->mqtt_port = MQTT_PORT;
  cfg->mqtt_data_topic = MQTT_DATA_TOPIC;
  cfg->mqtt_command_topic = MQTT_COMMAND_TOPIC;
  cfg->data_send_freq = DATA_SEND_FREQ;
  cfg->command_reception_frequency = COMMAND_RECEPTION_FREQ;

  cfg->sensor_list[0]->setPin(SENSOR1_PIN);
  cfg->sensor_list[0]->setType(SENSOR1_TYPE);
  cfg->sensor_list[1]->setPin(SENSOR2_PIN);
  cfg->sensor_list[1]->setType(SENSOR2_TYPE);
  cfg->sensor_list[2]->setPin(SENSOR3_PIN);
  cfg->sensor_list[2]->setType(SENSOR3_TYPE);

  return true;
}

/**
 * Write FW Configs to Flash
 */
bool writeConfigtoFlash(const SIS_Config *cfg) 
{
  String sensor_str;

  preferences.begin("config", false);

  // preferences.putInt("sensor_pin", cfg->sensorCfg.getPin());
  // preferences.putInt("sensor_refresh", cfg->sensorCfg.getReadFreq());
  // preferences.putInt("sensor_samples", cfg->sensorCfg.getSamplesNb());
  // preferences.putInt("sensor_type", (int)cfg->sensorCfg.getType());

  preferences.putString("wifi_ssid", cfg->wifi_ssid);
  preferences.putString("wifi_pwd", cfg->wifi_pwd);

  preferences.putString("mqtt_broker", cfg->mqtt_broker);
  preferences.putInt("mqtt_port", cfg->mqtt_port);
  preferences.putString("mqtt_data_topic", cfg->mqtt_data_topic);
  preferences.putString("mqtt_recv_topic", cfg->mqtt_command_topic);
  preferences.putULong("data_send_freq", cfg->data_send_freq);
  preferences.putULong("recv_interval", cfg->command_reception_frequency);

  for (int i = 0; i < SENSORS_NB; i++)
  {
    sensor_str = "sensor" + String(i) + "_type";
    preferences.putInt(sensor_str.c_str(), cfg->sensor_list[i]->getType());

    sensor_str = "sensor" + String(i) + "_pin";
    preferences.putInt(sensor_str.c_str(), cfg->sensor_list[i]->getPin());
  }

  preferences.end();
  return true;
}

/**
 * Read Flash to set System Configs
 */
bool readConfigFromFlash(SIS_Config *cfg)
{
  String sensor_str;

  if (!preferences.begin("config", true)) {  // read-only
    Serial.println("NVS namespace 'config' failed to open.");
    return false;
  }

  // Check if a known key exists to determine if config is stored
  if (!preferences.isKey("sensor_pin")) {
    Serial.println("No config found in NVS.");
    preferences.end();
    return false;
  }

  // cfg->sensorCfg.setPin(preferences.getInt("sensor_pin", SENSOR_PIN)); 
  // SENSOR_PIN is the default config if value not found in NVS
  // cfg->sensorCfg.setType((SensorType)preferences.getInt("sensor_type", SENSOR_MOISTURE));
  // cfg->sensorCfg.setDescription(preferences.getString("sensor_desc", SENSOR_DESCRIPTION));
  // cfg->sensorCfg.setReadFreq(preferences.getInt("sensor_refresh", SENSOR_REFRESH_MS));
  // cfg->sensorCfg.setSamplesNb(preferences.getInt("sensor_samples", SENSOR_SAMPLES));
  

  cfg->wifi_ssid = preferences.getString("wifi_ssid", WIFI_SSID);
  cfg->wifi_pwd = preferences.getString("wifi_pwd", WIFI_PASSWORD);

  cfg->mqtt_broker = preferences.getString("mqtt_broker", MQTT_BROKER);
  cfg->mqtt_port = preferences.getInt("mqtt_port", MQTT_PORT);
  cfg->mqtt_data_topic = preferences.getString("mqtt_data_topic", MQTT_DATA_TOPIC);
  cfg->mqtt_command_topic = preferences.getString("mqtt_recv_topic", MQTT_COMMAND_TOPIC);
  cfg->data_send_freq = preferences.getULong("data_send_freq", DATA_SEND_FREQ);
  cfg->command_reception_frequency = preferences.getULong("recv_interval", COMMAND_RECEPTION_FREQ);

  for (int i = 0; i < SENSORS_NB; i++)
  {
    sensor_str = "sensor" + String(i) + "_type";
    cfg->sensor_list[i] = new Sensor((SensorType) preferences.getInt(sensor_str.c_str(), 0));
    Serial.print(sensor_str + " : " + (String)cfg->sensor_list[i]->getType());

    sensor_str = "sensor" + String(i) + "_pin";
    cfg->sensor_list[i]->setPin(preferences.getInt(sensor_str.c_str(), 0));
    Serial.print(sensor_str + " : " + (String)cfg->sensor_list[i]->getPin());
  }
  
  preferences.end();
  return true;
}

/**
 * Read JSON config File to set configs
 */
bool readConfigFromJSON(SIS_Config *cfg)
{
  File file = SPIFFS.open("/sis_cfg.json", "r");
  if (!file) return false;

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, file);
  file.close();
  if (err) return false;

  JsonArray sensors = doc["sensor_configs"];
  if (!sensors.isNull() && sensors.size() > 0) {
    JsonObject sensor = sensors[0];
  //   cfg->sensorCfg.setPin(sensor["sensor_pin"] | 0);
  //   cfg->sensorCfg.setDescription(sensor["sensor_description"] | "No Sensor");
  //   cfg->sensorCfg.setReadFreq(sensor["sensor_refresh_ms"] | 5000);
  //   cfg->sensorCfg.setSamplesNb(sensor["sensor_samples"] | 25);

  //   String typeStr = sensor["sensor_type"] | "none";
  //   if (typeStr == "moisture") cfg->sensorCfg.setType(SENSOR_MOISTURE);
  //   else if (typeStr == "humidity") cfg->sensorCfg.setType(SENSOR_HUMIDITY);
  //   else if (typeStr == "temperature") cfg->sensorCfg.setType(SENSOR_TEMPERATURE);
  //   else cfg->sensorCfg.setType(SENSOR_NONE);
  }

  cfg->wifi_ssid = doc["network_settings"]["wifi_ssid"] | "";
  cfg->wifi_pwd = doc["network_settings"]["wifi_pwd"] | "";

  cfg->mqtt_broker = doc["mqtt_configs"]["mqtt_broker"] | "";
  cfg->mqtt_port = doc["mqtt_configs"]["mqtt_port"] | 1883;
  cfg->mqtt_data_topic = doc["mqtt_configs"]["mqtt_data_topic"] | "";
  cfg->mqtt_command_topic = doc["mqtt_configs"]["mqtt_command_topic"] | "";
  cfg->data_send_freq = doc["mqtt_configs"]["data_send_freq"] | 3000;
  cfg->command_reception_frequency = doc["mqtt_configs"]["command_reception_frequency"] | 500;

  return true;
}

/**
 * Compare 2 FW Configs
 */
bool areConfigsEqual(const SIS_Config *a, const SIS_Config *b)
{
  return a->wifi_ssid == b->wifi_ssid &&
         a->wifi_pwd == b->wifi_pwd &&
         a->mqtt_broker == b->mqtt_broker &&
         a->mqtt_port == b->mqtt_port &&
         a->mqtt_data_topic == b->mqtt_data_topic &&
         a->mqtt_command_topic == b->mqtt_command_topic &&
         a->data_send_freq == b->data_send_freq &&
         a->command_reception_frequency == b->command_reception_frequency;
}

bool writeConfigFile(const String& json)
{
  File file = SPIFFS.open("/sis_cfg.json", "w");
  if (!file) return false;
  file.print(json);
  file.close();
  return true;
}
