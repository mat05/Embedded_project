#include <arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DHT_U.h>
#include <PubSubClient.h>

// Pin def.
const int DHT_PIN = 13;
const int POT_PIN = A0;

// const def.
const bool DEBUG = true;
const int POT_MAX = 1024;
const int POT_MIN = 15;

// WiFi credentials def.
const char *SSID = "Redmi Note 10 Pro";
const char *PWD = "chipouille";

// MQTT client def.
const char *mqttServer = "192.168.241.215";
const int mqttPort = 1883;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
const String clientId = "ESP8266Client";
const String user = "jules";
const String pwd = "juju";

// DHT sensor def.
DHT dht(DHT_PIN, DHT11);

// Creates a connection using declared WiFi credentials.
void connectToWiFi()
{
  Serial.print("\nConnecting to ");
  Serial.println(SSID);

  // Begins connection to declared SSID using declared PWD.
  WiFi.begin(SSID, PWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Connects to the mqtt Broker
void connectToBroker()
{
  // Setting the server on which the broker is installed.
  mqttClient.setServer(mqttServer, mqttPort);

  // setting the callback function.
  // mqttClient.setCallback(callback);

  // Connecting to the MQTT broker.
  Serial.println("Connecting to MQTT Broker");
  while (!mqttClient.connected())
  {
    delay(500);
    Serial.print(".");

    // Connecting to the mqtt broker using the clientId.
    if (mqttClient.connect(clientId.c_str(), user.c_str(), pwd.c_str()))
    {
      Serial.println("\nConnected.\n");
      // subscribe to topic.
      // mqttClient.subscribe("CurrentDateTime");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\nStart\n-----------------------------------------");
  // Connecting to WiFi.
  connectToWiFi();

  // Connecting to MQTT broker.
  connectToBroker();

  // Setting DHT pins and pinMode.
  dht.begin();
}

// Attempts to publish a message to the MQTT broker.

void loop()
{
  // Reconnect to WiFi if connection died.
  if (WiFi.status() != WL_CONNECTED)
  {
    connectToWiFi();
  }

  // Reconnect to mqtt broker if connection died.
  if (!mqttClient.connected())
  {
    connectToBroker();
  }

  // Delay between measurements.
  int msDelay = 4000;
  delay(msDelay);

  // Data acquisition
  // Get Pot value.
  int potValue = analogRead(POT_PIN);
  float potRatio = float(potValue) / float(POT_MAX);
  // Get temperature.
  float temp = dht.readTemperature();
  // Get humidity.
  float hum = dht.readHumidity();

  // Publish data on topic using MQTT.
  char TemperatureDataMessage[6];
  dtostrf(temp * potRatio, 5, 2, TemperatureDataMessage);
  char HumidityDataMessage[6];
  dtostrf(hum, 5, 2, HumidityDataMessage);

  Serial.println("Attempting to publish Temperature data.");
  if (mqttClient.publish("ESPTemp", TemperatureDataMessage))
  {
    Serial.println("Message published!\n");
  }
  else
  {
    Serial.println("Publication failed!\n");
    Serial.println(mqttClient.state());
  }
  Serial.println("Attempting to publish Humidity data.");
  if (mqttClient.publish("ESPHum", HumidityDataMessage))
  {
    Serial.println("Message published!\n");
  }
  else
  {
    Serial.println("Publication failed!\n");
    Serial.println(mqttClient.state());
  }

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