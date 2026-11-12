# Project 03 — Automatic Night Lamp Using ESP32

## About the Project

For my third ESP32 project, I wanted to build a simple automatic night lamp that turns on when it gets dark and switches off when there's enough light.

Unlike my previous projects, where I controlled an LED through code or a push button, this was my first time using a sensor to make the ESP32 respond automatically to its surroundings.

The idea was simple, but getting the sensor to work properly turned out to be more challenging than I expected!

## Components Used

- ESP32 DevKit V1
- LDR light sensor module (LM393-based)
- Red LED
- 220Ω resistor
- Breadboard
- Jumper wires
- USB data cable
- Digital multimeter (for troubleshooting)

## Software

- Visual Studio Code
- PlatformIO
- Arduino framework (C++)

## Circuit Connections

I used GPIO 18 to read the light sensor's digital output and GPIO 23 to control the external LED.

**LDR Sensor Module**

| Sensor Pin | ESP32 Pin |
|---|---|
| VCC | 3V3 |
| GND | GND |
| DO | GPIO 18 (D18) |

**LED Circuit**

GPIO 23 → 220Ω resistor → LED anode (+) → LED cathode (−) → GND

Both the sensor and LED share a common GND connection.

The LDR module has a small potentiometer that allows the light-detection threshold to be adjusted.

## Source Code

File: `src/main.cpp`

```cpp
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
```

## How It Works

The LDR changes its resistance depending on the amount of light falling on it.

- More light → Lower resistance
- Less light → Higher resistance

The sensor module uses an LM393 comparator to compare the light-dependent signal against an adjustable reference voltage.

Based on this comparison, the module produces a digital HIGH or LOW signal through its DO pin.

The ESP32 reads this signal through GPIO 18 using `digitalRead()`.

In my setup:

- **Darkness:** The sensor produces HIGH, and the external LED turns ON.
- **Sufficient light:** The sensor produces LOW, and the external LED turns OFF.

I used `INPUT_PULLUP` to enable the ESP32's internal pull-up resistor on GPIO 18.

The program checks the sensor every 100 milliseconds and updates the LED accordingly.

## Challenges and Troubleshooting

This project took considerably longer than my previous two because I ran into several problems while trying to understand the sensor and its connections.

### 1. The LED Wasn't Responding Properly

Initially, the external LED either stayed ON or OFF continuously, regardless of whether I covered the LDR or shone light on it.

I wasn't sure whether the issue was with the sensor, ESP32, code, or wiring.

Instead of changing everything at once, I started testing individual parts of the circuit.

### 2. Testing the ESP32 and External LED

I first checked whether the ESP32 was executing the uploaded program by running the basic GPIO 2 blinking code.

The onboard blue LED blinked successfully.

I then tested the external LED independently using GPIO 23.

After uploading a simple blinking program, the external red LED blinked correctly.

This confirmed that the LED, resistor, and GPIO 23 output circuit were working.

### 3. Testing GPIO 18

Next, I tested GPIO 18 using `INPUT_PULLUP`.

With nothing connected to GPIO 18, the external LED stayed OFF.

When I connected GPIO 18 directly to GND, the LED turned ON.

This helped me confirm that GPIO 18 could detect changes between HIGH and LOW.

I also learned how important it is to disconnect the intended wires before testing. At one point, I thought GPIO 18 was disconnected when it was actually still connected, which led to confusing results.

### 4. Confusing VCC and DO

This was probably my biggest mistake during the project.

While measuring the sensor's output voltage, I repeatedly got a reading of approximately 3.3 V.

I initially thought the sensor wasn't responding to light.

Later, I realised that I had been measuring **VCC instead of DO**.

VCC is the sensor's power supply pin, so it is supposed to remain at approximately 3.3 V.

DO, on the other hand, is the digital output that communicates the sensor's detection state to the ESP32.

This taught me to identify pin labels carefully before making connections or taking measurements.

### 5. Testing the LDR

I also used my multimeter to measure the LDR's resistance under different lighting conditions.

| Condition | Approximate Resistance |
|---|---|
| Phone flashlight shining on LDR | 7 kΩ |
| LDR covered | 9 kΩ |

The resistance increased when I covered the sensor, which was consistent with the expected behaviour of an LDR.

Since the LDR was still attached to the module, the readings may have been influenced by the surrounding circuitry.

### 6. Adjusting the Sensor Threshold

My sensor module has a blue potentiometer that adjusts the light level at which its digital output changes.

I experimented with this adjustment and observed the sensor's indicator responding to changes in light.

Eventually, I was able to get the external LED responding correctly.

However, I noticed that the sensor responded reliably when I used my phone's flashlight, but not consistently under normal room lighting.

This showed me that getting a circuit to work and getting it to perform reliably in everyday conditions are two different things.

The sensor's threshold still needs further calibration.

## Result

Successfully built a working automatic night lamp using an ESP32 and an LDR sensor module.

The circuit behaves as intended when tested with sufficiently different light levels:

- **Darkness:** External red LED turns ON.
- **Bright light from phone flashlight:** External red LED turns OFF.

The sensor does not yet respond consistently to ordinary room lighting, so the project still needs calibration before it can function as a practical night lamp.

## What I Learned

Through this project, I learned:

- How an LDR detects changes in light through resistance.
- How an LM393 comparator produces a digital output.
- The difference between VCC, GND, and DO.
- How to interface a digital sensor with an ESP32.
- How `digitalRead()` and `INPUT_PULLUP` work.
- How to use a multimeter to measure voltage, resistance, and continuity.
- How to test GPIO inputs and outputs independently.
- Why checking the correct pins is important.
- How potentiometers adjust sensor thresholds.
- How to troubleshoot a circuit systematically instead of changing connections randomly.
- The difference between a functioning prototype and a reliably calibrated device.

## Future Improvements

- Calibrate the sensor to distinguish normal room lighting from darkness.
- Experiment with different light-detection thresholds.
- Explore using a bare LDR and an analog voltage divider for more precise light measurements.
- Add software filtering or hysteresis to prevent unwanted switching near the threshold.
- Replace the small indicator LED with a brighter, low-voltage lamp.

---

*Project 03 | ESP32 Embedded Systems Learning Journey*
