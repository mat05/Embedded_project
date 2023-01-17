#include <Arduino.h>
#define POT_VOUT GPIO_NUM_15
#define DHT_DATA1 GPIO_NUM_13
#define DHT_DATA2 GPIO_NUM_12

void setup()
{
  Serial.begin(115200);
  // Pot used to simulate changes in temp
  pinMode(POT_VOUT, GPIO_MODE_INPUT);
  // DHT Data 1 (TBD temp or hygro)
  pinMode(DHT_DATA1, GPIO_MODE_INPUT);
  // DHT Data 2 (TBD temp or hygro)
  pinMode(DHT_DATA2, GPIO_MODE_INPUT);
  Serial.print("Start-----------------------------------");
}

void loop()
{
  // default: asleep
  // if: every t time, temperature < TempMin:
  //     wake up, DHT data -> RasPi via MQTT
  //
  // OR
  //
  // default: asleep
  // if: night time:
  //     wake up every t time, DHT data -> RasPi via MQTT
  // (sunlight detector needed)

  Serial.print(analogRead(POT_VOUT));
}