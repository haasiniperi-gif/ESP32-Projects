# Project 04 — Smart Day/Night Environmental Monitor

## About the Project

After experimenting with the DHT11 temperature and humidity sensor, I wanted to combine it with the light sensor from my previous project.

The idea was to create a system that automatically switches between day and night modes.

During the day, a blue LED would remain ON while the red LED stayed OFF. When darkness was detected, the red LED would turn ON, the blue LED would turn OFF, and the ESP32 would start displaying temperature and humidity readings.

This was my first attempt at combining multiple sensors and outputs into a single circuit instead of testing them individually.

## Components Used

- ESP32 DevKit V1
- LDR light sensor module (LM393-based)
- DHT11 temperature and humidity sensor module
- Red LED
- Blue LED
- Two 220Ω resistors
- Breadboard
- Jumper wires
- USB data cable
- Digital multimeter

## Software

- Visual Studio Code
- PlatformIO
- Arduino framework (C++)
- Adafruit DHT Sensor Library
- Adafruit Unified Sensor Library

## Circuit Connections

I used four GPIO pins to connect the two sensors and two LEDs.

| Component | ESP32 Connection |
|---|---|
| LDR DO | GPIO 18 |
| DHT11 DATA | GPIO 19 |
| Red LED anode (+) | GPIO 23 through 220Ω resistor |
| Blue LED anode (+) | GPIO 22 through 220Ω resistor |
| LDR VCC | 3V3 |
| DHT11 VCC | 3V3 |
| LDR GND | GND |
| DHT11 GND | GND |
| Red LED cathode (−) | GND |
| Blue LED cathode (−) | GND |

I used the breadboard's power rails to distribute 3.3 V and GND to the components.

Each LED has its own current-limiting resistor.

## Source Code

File: `src/main.cpp`

```cpp
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

  bool isDark = (digitalRead(LDR_PIN) == HIGH);

  if (isDark) {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);

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

    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
  }

  wasDark = isDark;
}
```

## PlatformIO Configuration

File: `platformio.ini`

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

monitor_speed = 115200

lib_deps =
    adafruit/DHT sensor library
    adafruit/Adafruit Unified Sensor
```

The DHT libraries handle communication with the temperature and humidity sensor.

The Serial Monitor is configured to communicate at 115200 baud.

## How It Works

The system uses an LDR sensor module to detect whether the surroundings are bright or dark.

The LDR changes resistance depending on the amount of light falling on it. The LM393 comparator on the module compares the light-dependent signal against an adjustable threshold and produces a digital output.

The ESP32 reads this output through GPIO 18 and decides which mode to activate.

### Day Mode

When sufficient light is detected:

- The red LED remains OFF.
- The blue LED turns ON.
- Temperature and humidity measurements are paused.

### Night Mode

When darkness is detected:

- The red LED turns ON.
- The blue LED turns OFF.
- The ESP32 reads temperature and humidity from the DHT11.
- The measurements are displayed in Serial Monitor approximately every 30 seconds.

The code assumes the LDR module outputs HIGH in darkness and LOW in sufficient light, based on my previous light sensor project.

### Using millis()

Instead of using a 30-second `delay()`, I used `millis()` to track the time between sensor readings.

This allows the ESP32 to keep checking the light sensor while waiting for the next temperature and humidity measurement.

I also used a Boolean variable called `wasDark` to remember whether the previous loop detected darkness.

This allows the program to attempt a temperature and humidity reading when it first enters night mode, rather than waiting for the full 30-second interval.

## Challenges and Troubleshooting

This project was more challenging than my previous ones because I had to manage multiple components and their connections at the same time.

### 1. Distributing Power Through the Breadboard

Since I had limited accessible 3V3 and GND pins on my ESP32, I decided to use the breadboard's power rails to distribute power to the sensors.

Initially, I assumed that every hole along a power rail was connected internally.

However, I noticed that components worked when placed close to the jumper wires supplying power, but stopped working when moved towards the other end of the breadboard.

After testing the rails using my multimeter's continuity mode, I discovered that my breadboard had split power rails.

The two sections were electrically separate, so components placed on the disconnected sections weren't receiving the required power or ground connection.

I fixed this by using jumper wires to bridge the separate sections of the 3V3 and
