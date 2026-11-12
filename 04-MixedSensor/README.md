# Project 04 — Smart Day/Night Environmental Monitor

## About the Project

After experimenting with the DHT11 temperature and humidity sensor, I wanted to combine it with the LDR light sensor from my previous project.

I built a system that automatically switches between day and night modes depending on the surrounding light.

During the day, the blue LED stays ON while the red LED remains OFF. When darkness is detected, the red LED turns ON, the blue LED turns OFF, and the ESP32 starts displaying temperature and humidity readings.

This was my first project involving multiple sensors and outputs working together, rather than testing individual components separately.

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
- Digital multimeter (for troubleshooting)

## Software

- Visual Studio Code
- PlatformIO
- Arduino framework (C++)
- Adafruit DHT Sensor Library
- Adafruit Unified Sensor Library

## Circuit Connections

I used four GPIO pins to connect the sensors and LEDs.

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

<img width="959" height="704" alt="image" src="https://github.com/user-attachments/assets/04ad944d-eb37-4b5b-a2ff-f011a08c20fa" />


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

The system uses an LDR sensor module to detect changes in the surrounding light.

The LDR changes its resistance depending on the amount of light falling on it. The LM393 comparator on the module compares the light-dependent signal against an adjustable threshold and produces a digital HIGH or LOW output.

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

The code uses `millis()` instead of a long `delay()` to track the time between readings.

This allows the ESP32 to continue checking the light sensor while waiting for the next temperature and humidity measurement.

I also used a Boolean variable called `wasDark` to remember whether the system was previously in day or night mode.

When the system first enters night mode, the program attempts a temperature and humidity reading immediately rather than waiting for the full 30-second interval.

## Challenges and Troubleshooting

This project was more challenging than my earlier ones because I had to manage multiple components and their connections at the same time.

### 1. Split Breadboard Power Rails

One of the biggest problems I faced was with the breadboard's power rails.

Since the ESP32 had limited accessible 3V3 and GND pins, I decided to use the breadboard rails to distribute power to the sensors and LEDs.

Initially, I assumed that every hole along a rail was electrically connected.

However, I noticed that components worked when placed close to the power jumper wires but stopped working when moved towards the opposite end of the breadboard.

After testing the rails using my multimeter's continuity mode, I discovered that my breadboard had split power rails.

The two sections were electrically separate, so components placed on the disconnected sections weren't receiving the required power or ground connection.

I fixed this by using jumper wires to bridge the separate sections of the 3V3 and GND rails.

This taught me that even when the code and components are working correctly, an incomplete power connection can prevent the entire circuit from functioning.

### 2. Troubleshooting the LED Circuits

Initially, neither LED behaved as expected.

I tested the red and blue LED circuits separately using simple GPIO programs.

I checked whether GPIO 23 and GPIO 22 could produce HIGH output voltages and used continuity mode to trace the connections through the resistors and LEDs.

The red LED eventually worked correctly.

The blue LED was initially very dim, so I tried replacing it with another LED. However, the replacement behaved similarly.

This made me investigate the breadboard connections and power distribution more carefully rather than assuming the LED itself was faulty.

After correcting the connections, I was able to get both LEDs working as intended.

### 3. Measuring GPIO Voltages

I used the multimeter to check whether the ESP32 was producing the expected voltage at its output pins.

For example, GPIO 22 measured approximately 3.3 V when configured HIGH with the LED circuit disconnected.

However, the blue LED circuit initially did not behave as expected when connected.

This helped me understand why testing a GPIO independently and testing it as part of a complete circuit can give different results.

### 4. Troubleshooting Serial Monitor

While experimenting with the DHT11 sensor, I encountered problems with Serial Monitor displaying unreadable characters.

I checked the baud rate in my C++ program and PlatformIO configuration.

I also encountered serial port errors when trying to open a port that was already in use.

Later, the ESP32's serial port changed between USB connections.

I learned to identify the currently available serial port using:

```bash
pio device list
```

And open Serial Monitor using the detected port:

```bash
pio device monitor -p /dev/cu.usbserial-120 -b 115200
```

The port name may change depending on the USB connection.

### 5. Calibrating the Light Sensor

In Project 03, my LDR sensor initially responded reliably only when I used my phone's flashlight.

After further adjustments and testing, I was able to get it responding to normal room lighting as well.

This made the day/night switching system more practical because I no longer needed to shine a flashlight directly onto the sensor to trigger a change.

I learned that a sensor can be functioning correctly but still require calibration to work reliably under real environmental conditions.

### 6. Combining Multiple Sensors

In my earlier projects, I only had to focus on one input or output at a time.

This project required me to assign separate GPIO pins, share the power supply and ground connections, and coordinate multiple components through one program.

I learned that testing components individually before combining them makes troubleshooting much easier.

## What I Learned

Through this project, I learned:

- How to integrate multiple sensors and LEDs with one ESP32.
- How to assign GPIO pins for different inputs and outputs.
- How to implement day and night modes using conditional statements.
- How to use Boolean variables to remember previous states.
- How `millis()` can be used for non-blocking timing.
- How to read temperature and humidity using the DHT11 library.
- How to distribute 3.3 V and GND using breadboard power rails.
- Why some breadboards have split power rails.
- How to identify disconnected sections using continuity testing.
- How to measure GPIO output voltages.
- How to isolate components while troubleshooting.
- How to identify and configure serial ports in PlatformIO.
- How to calibrate a light sensor for normal room lighting.

## Result

Successfully built a Smart Day/Night Environmental Monitor using an ESP32, LDR light sensor, DHT11 sensor, and two LEDs.

The complete system automatically switches between day and night modes based on the surrounding light.

| Environment | Red LED | Blue LED | Temperature & Humidity |
|---|---|---|---|
| Daylight | OFF | ON | Readings paused |
| Darkness | ON | OFF | Readings every 30 seconds |

The LDR sensor responds to normal room lighting without requiring a phone flashlight.

Both LEDs switch according to the detected light conditions, and temperature and humidity readings are displayed through Serial Monitor during night mode.

One of the biggest challenges was discovering and correcting the split breadboard power rails, which had initially prevented several components from working properly.

