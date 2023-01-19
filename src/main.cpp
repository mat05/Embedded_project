// https://www.survivingwithandroid.com/esp32-mqtt-client-publish-and-subscribe/
#include <arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DHT_U.h>
// #include <PubSubClient.h>
//  https://github.com/knolleary/pubsubclient

// Pin def
const int DHT_PIN = 13;
const int POT_PIN = A0;

// const def
const bool DEBUG = true;
const int POT_MAX = 1024;
const int POT_MIN = 15;

// WiFi def
const char *SSID = "Redmi Note 9";
const char *PWD = "12345678";

// MQTT client def
// https://www.hivemq.com/blog/mqtt-raspberrypi-part01-sensor-data-hivemqcloud-java-pi4j/
const WiFiClient wifiClient;
// const PubSubClient mqttClient(wifiClient);
const char *mqttServer = "";
const int mqttPort = 9999;

// Sensors detection delay
uint32_t delayMS;

// DHT sensor def
DHT dht(DHT_PIN, DHT11);

// Creates a connection to the declared WiFi
void connectToWiFi()
{
  Serial.print("Connecting to ");

  // Begins connection to declared SSID using declared PWD
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);

  Serial.print("Connected.");
}

// Set up the MQTT client to communicate with the RasPi
/*
void setupMQTT()
{
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);
}

// Connects the ESP to the Hivemq MQTT broker
void connectToBroker()
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected())
  {
    Serial.println("Reconnecting to MQTT Broker..");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str()))
    {
      Serial.println("Connected.");
      // subscribe to topic
      mqttClient.subscribe("/swa/commands");
    }
  }
}
*/

float fahrenheitToCelsius(float fahrenheit)
{
  float celsius;

  celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
  return celsius;
}

void setup()
{
  Serial.begin(115200);
  // connectToWiFi();
  // setupMQTT();
  dht.begin();
  /*
  dht.temperature().getSensor(&sensor);
  Serial.println(F("Temperature:"));
  Serial.print(F("Max Value:   "));
  Serial.print(fahrenheitToCelsius(sensor.max_value));
  Serial.println(F("°C"));
  Serial.print(F("Min Value:   "));
  Serial.print(fahrenheitToCelsius(sensor.min_value));
  Serial.println(F("°C"));
  Serial.print(F("Resolution:  "));
  Serial.print(fahrenheitToCelsius(sensor.resolution));
  Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Hygro sensor
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity:"));
  Serial.print(F("Max Value:   "));
  Serial.print(sensor.max_value);
  Serial.println(F("%"));
  Serial.print(F("Min Value:   "));
  Serial.print(sensor.min_value);
  Serial.println(F("%"));
  Serial.print(F("Resolution:  "));
  Serial.print(sensor.resolution);
  Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  */
}

void loop()
{
  // establishing connection to the WiFi
  // connectToWiFi();
  // setting up MQTT client

  int potValue = analogRead(POT_PIN);
  float potRatio = float(potValue) / float(POT_MAX);

  // Delay between measurements.
  int delayMS = 800;
  delay(delayMS);
  // Get temperature.
  float temp = dht.readTemperature();
  // Get humidity.
  float hum = dht.readHumidity();

  if (DEBUG)
  {
    Serial.print("Pot value: ");
    Serial.println(potValue);

    Serial.print("Temperature: ");
    Serial.print(temp * potRatio);
    Serial.println("°C");

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("%");

    Serial.println("---------------------------------------");
  }
}