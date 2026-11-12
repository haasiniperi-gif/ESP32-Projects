
#include <Arduino.h>
#include <DHT.h>

#define LDR_PIN 18
#define DHT_PIN 19

#define RED_LED 23
#define BLUE_LED 22

#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

const unsigned long interval = 30000;
unsigned long lastReading = 0;

bool wasDark = false;

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LDR_PIN, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  Serial.println("Smart Day/Night Monitor Started");
}

void loop() {

  // HIGH means darkness for our LDR setup
  bool isDark = (digitalRead(LDR_PIN) == HIGH);

  if (isDark) {

    // Night mode
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);

    // Read DHT11 every 30 seconds
    if (!wasDark || millis() - lastReading >= interval) {

      float temperature = dht.readTemperature();
      float humidity = dht.readHumidity();

      if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Sensor reading failed!");
      }
      else {
        Serial.println("NIGHT MODE");

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        Serial.println("--------------------");
      }

      lastReading = millis();
    }
  }
  else {

    // Day mode
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }

  wasDark = isDark;
}
