# Project 01: LED Blinking Using ESP32

## Overview

This project marks my first step into hands-on electronics and embedded systems.

The objective was to interface an external LED with an ESP32 microcontroller and control its blinking using GPIO (General Purpose Input/Output) pins.

Through this project, I explored basic hardware connections, digital output control, and microcontroller programming.

## Components Required

| Component | Quantity |
|---|---|
| ESP32 DevKit V1 | 1 |
| Red LED | 1 |
| 220Ω Resistor | 1 |
| Breadboard | 1 |
| Jumper Wires | 2 |
| USB Data Cable | 1 |


## Connections
<img width="978" height="727" alt="image" src="https://github.com/user-attachments/assets/e968a083-2bf0-47e5-8816-6aaaa70e3a27" />
<img width="967" height="713" alt="image" src="https://github.com/user-attachments/assets/82d60fd7-c20a-4510-a08b-476548e6df98" />



## Software and Technologies

- **Microcontroller:** ESP32
- **Programming Language:** C++
- **Framework:** Arduino
- **Development Environment:** Visual Studio Code
- **Extension:** PlatformIO

## Circuit Connections

The external LED is connected to GPIO 2 of the ESP32 through a current-limiting resistor.

| ESP32 / Component | Connection |
|---|---|
| GPIO 2 (D2) | 220Ω resistor |
| Resistor | LED anode (+) |
| LED cathode (−) | ESP32 GND |

The resistor limits the current through the LED, while GND provides the return path to complete the circuit.

## Source Code

```cpp
#include <Arduino.h>

#define LED_PIN 2

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);

    digitalWrite(LED_PIN, LOW);
    delay(1000);
}
```

## Working Principle

1. The ESP32 is powered through a USB connection.
2. GPIO 2 is configured as a digital output using `pinMode()`.
3. `digitalWrite(LED_PIN, HIGH)` sets the GPIO output HIGH, turning the LED on.
4. `delay(1000)` maintains this state for one second.
5. `digitalWrite(LED_PIN, LOW)` sets the output LOW, turning the LED off.
6. The program repeats continuously through the `loop()` function.

The LED therefore follows a repeating ON/OFF cycle with a two-second period.

## Challenges and Troubleshooting

During the initial setup, the onboard blue LED blinked successfully, but the external LED did not respond.

This led me to investigate:

- The difference between onboard and external LEDs.
- GPIO pin numbering and physical pin locations.
- The importance of matching the GPIO number in the code with the physical connection.
- Breadboard connectivity and jumper wire placement.
- The role of GND in completing an electrical circuit.

After checking and correcting the connections, the external LED blinked successfully.

## Key Learnings

- Understanding GPIO pins and their functions.
- Configuring digital outputs using `pinMode()`.
- Controlling output states using `digitalWrite()`.
- Using `delay()` to introduce timing.
- Understanding LED polarity and current-limiting resistors.
- Building and troubleshooting a basic breadboard circuit.
- Uploading firmware to an ESP32 using PlatformIO.

## Result

Successfully implemented an LED blinking circuit using the ESP32 microcontroller.

The LED turns on for one second and off for one second, continuously.



---

*Project 01 | ESP32 Embedded Systems Learning Journey*
