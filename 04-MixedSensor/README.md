# Project 04 — Smart Day/Night Environmental Monitor

## About the Project

After experimenting with the DHT11 temperature and humidity sensor, I wanted to combine it with the light sensor from my previous project.

The idea was to create a system that automatically switches between day and night modes.

During the day, the blue LED stays ON while the red LED remains OFF. When darkness is detected, the red LED turns ON, the blue LED turns OFF, and the ESP32 displays temperature and humidity readings every 30 seconds.

This was my first attempt at combining multiple sensors and outputs into one circuit instead of testing them individually.

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

I used the breadboard's power rails to distribute 3.3 V and GND to the components. Each LED has its own current-limiting resistor.

<img width="973" height="690" alt="image" src="https://github.com/user-attachments/assets/4cbf8799-9ac7-405f-8b52-d94d5a563b1a" />


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

## How It Works

The LDR sensor detects changes in the surrounding light and sends a digital HIGH or LOW signal to the ESP32.

The ESP32 uses this signal to switch between two operating modes.

### Day Mode

When sufficient light is detected:

- The red LED remains OFF.
- The blue LED turns ON.
- Temperature and humidity readings are paused.

### Night Mode

When darkness is detected:

- The red LED turns ON.
- The blue LED turns OFF.
- The ESP32 reads temperature and humidity from the DHT11.
- Measurements appear in Serial Monitor approximately every 30 seconds.

The program uses `millis()` to manage the time between measurements without stopping the ESP32 from checking the light sensor.

A Boolean variable called `wasDark` tracks the previous light condition, allowing the program to attempt a reading when it first enters night mode.

## Challenges and Troubleshooting

### 1. Split Breadboard Power Rails

One of the biggest problems I faced was with the breadboard's power rails.

Initially, I assumed that every hole along a rail was connected internally.

However, components worked when placed close to the power jumper wires but stopped working when moved towards the other end.

After checking continuity with my multimeter, I discovered that the breadboard had split power rails.

I fixed this by bridging the separate sections of the 3V3 and GND rails using jumper wires.

### 2. Troubleshooting the LEDs

Initially, neither LED behaved as expected.

I tested the red and blue LED circuits separately using simple GPIO programs.

I checked the output voltages, LED polarity, resistor connections, and continuity through the breadboard.

The blue LED was initially very dim. Replacing it didn't immediately solve the problem, which made me investigate the wiring and power distribution more carefully.

### 3. Serial Monitor Issues

While working with the DHT11, I encountered garbled Serial Monitor output and serial port errors.

I learned to check the baud rate, close existing Serial Monitor sessions, and identify the ESP32's current serial port using:

```bash
pio device list
```

I also learned that the serial port name can change after reconnecting the ESP32.

### 4. Calibrating the Light Sensor

In Project 03, my LDR sensor initially responded reliably only when I used my phone's flashlight.

After further adjustments and testing, I was able to get it responding to normal room lighting as well.

This helped me understand the importance of adjusting a sensor's detection threshold for the actual environment in which it will operate.

## What I Learned

- How to combine multiple sensors and outputs in one ESP32 project.
- How to assign separate GPIO pins to different components.
- How to use conditional logic to implement day and night modes.
- How to use `millis()` for timed sensor readings.
- How to use Boolean variables to track previous states.
- How to distribute power through breadboard rails.
- How to identify and fix split power rails.
- How to troubleshoot LED circuits using a multimeter.
- How to configure PlatformIO Serial Monitor.
- How to adjust an LDR sensor's threshold for normal room lighting.

## Result

The LDR sensor now responds to changes in normal room lighting without requiring a phone flashlight.

The split breadboard rail issue has also been resolved, and the individual LED and sensor circuits have been tested during development.

The complete day/night system is intended to operate as follows:

| Environment | Red LED | Blue LED | DHT11 |
|---|---|---|---|
| Daylight | OFF | ON | Readings paused |
| Darkness | ON | OFF | Readings every 30 seconds |
