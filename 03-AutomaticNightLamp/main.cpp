
#include <Arduino.h>

#define LDR_PIN 18
#define LED_PIN 23

void setup() {
  pinMode(LDR_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int lightState = digitalRead(LDR_PIN);

  if (lightState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(100);
}
