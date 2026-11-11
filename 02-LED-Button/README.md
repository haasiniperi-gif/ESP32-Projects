# Project 02 — Controlling an LED with a Push Button

## About the Project

For my second ESP32 project, I wanted to control an LED using a push button.

Instead of making the LED blink automatically like in Project 01, the goal was to turn it on when I pressed the button and turn it off when I released it.

This was my first time working with digital inputs.

## Components Used

- ESP32 DevKit V1
- Red LED
- 220Ω resistor
- Push button
- Breadboard
- Jumper wires
- USB cable

## Software

- VS Code
- PlatformIO
- Arduino framework (C++)

## Circuit Connections

I used two GPIO pins:

- **GPIO 23:** Controls the LED
- **GPIO 18:** Reads the push button

<img width="917" height="691" alt="image" src="https://github.com/user-attachments/assets/cb95a433-bec1-4df9-8048-ecfed815b845" />

<img width="853" height="524" alt="image" src="https://github.com/user-attachments/assets/301cf0be-ba54-40ba-8ad4-1cfaa2750f7e" />




**LED connections:**

GPIO 23 → 220Ω resistor → LED (+) → LED (−) → GND

**Button connections:**

GPIO 18 → Push button → GND

I used the ESP32's internal pull-up resistor, so I didn't need to connect the button to 3.3V separately.

## Code

```cpp
#include <Arduino.h>

#define LED_PIN 23
#define BUTTON_PIN 18

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH);
    }
    else {
        digitalWrite(LED_PIN, LOW);
    }
}
```

## How It Works

The ESP32 continuously checks whether the button is pressed.

Since I'm using `INPUT_PULLUP`, GPIO 18 normally reads HIGH.

When I press the button, it connects GPIO 18 to GND, making the input LOW.

The program detects this and turns the LED on. Releasing the button turns it off again.

## Problems I Faced

This project took me quite a bit longer than I expected!

Initially, the LED wouldn't respond when I pressed the button.

I wasn't sure whether the problem was with the button, the ESP32, or my connections.

I started by testing the push button with a multimeter in continuity mode. That's when I learned that some legs of a four-pin push button are already connected internally, while the other contacts connect only when the button is pressed.

I also learned that a continuous beep on the multimeter is normal as long as the connection is closed.

Even after confirming the button worked, the LED still wouldn't turn on.

To narrow things down, I tested the ESP32's onboard LED and then the external LED separately using GPIO 23.

Once I got the external LED blinking, I knew that part of the circuit was working.

I then went back to the button connections and checked the path between GPIO 18 and GND.

After correcting the wiring, the circuit finally worked!

The exact connection responsible for the original problem wasn't conclusively identified, but the process helped me understand how important it is to check every connection.

## What I Learned

- How digital inputs work
- How to use `digitalRead()`
- What `INPUT_PULLUP` means
- Why pressing the button produces a LOW signal
- How four-legged push buttons work internally
- How to test continuity using a multimeter
- How to check GPIO voltage
- Why common GND connections matter
- How to troubleshoot a circuit one part at a time

## Result

The LED now turns on when I press the button and turns off when I release it.

