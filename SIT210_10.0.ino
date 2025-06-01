#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define LED_PIN 3
#define BUZZER_PIN 4

BH1750 lightSensor;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lightSensor.begin();
  dht.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("Smart Light and Temperature Alert System Started");
}

void loop() {
  float lux = lightSensor.readLightLevel();
  float temp = dht.readTemperature();

  Serial.print("Lux: ");
  Serial.print(lux);
  Serial.print(" | Temp: ");
  Serial.println(temp);

  if (lux < 30 || temp > 30) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);  // Continuous beep
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  delay(1000);  // one reading per second
}
