# ESP32 Projects

Hi! Welcome to my ESP32 projects repository!

I'm currently learning electronics and embedded systems through small, hands-on projects. I started this repository to document what I build, the concepts I learn, and the challenges I face along the way.

I'm starting with basic circuits and gradually moving towards projects involving sensors, automation, and IoT.

My goal is to understand how hardware and software work together and become more confident in building and troubleshooting circuits independently.

## My Projects

| No. | Project | What I Explored | Status |
|---|---|---|---|
| 01 | LED Blinking | GPIO outputs, LED interfacing, basic programming | Completed |
| 02 | Button-Controlled LED | Digital inputs, push buttons, pull-up resistors | Completed |
| 03 | Automatic Night Lamp | LDR sensors, comparators, digital signals, calibration | Completed |
| 04 | Smart Day/Night Environmental Monitor | Multiple sensors, conditional logic, DHT11, power distribution, `millis()` | Completed |
| 05 | Ultrasonic Distance Meter | Ultrasonic sensing, time-of-flight measurement, voltage dividers | In Progress |
| 06 | Motion Detection System | PIR sensors | Planned |
| 07 | Wi-Fi Sensor Dashboard | IoT and wireless communication | Planned |

Each project has its own folder containing the source code, circuit connections, explanations, and the things I learned while building it.

## Hardware and Software

**Hardware**
- ESP32 DevKit V1
- Breadboard and jumper wires
- LEDs, resistors, and push buttons
- LDR light sensor module
- DHT11 temperature and humidity sensor
- HC-SR04 ultrasonic sensor
- Digital multimeter
- Other basic electronic components

**Software**
- Visual Studio Code
- PlatformIO
- Arduino framework (C++)
- Adafruit sensor libraries

## What I've Learned So Far

Through these projects, I've started getting comfortable with:

- Using GPIO pins as digital inputs and outputs.
- Understanding how microcontrollers interact with external components.
- Working with push buttons and internal pull-up resistors.
- Interfacing light, temperature, humidity, and distance sensors with the ESP32.
- Reading and displaying sensor measurements using Serial Monitor.
- Using external libraries in PlatformIO.
- Understanding how comparators and digital sensor outputs work.
- Combining multiple components into a single system.
- Using `millis()` to manage timed operations.
- Understanding ultrasonic sensing and time-of-flight measurements.
- Learning how voltage dividers protect 3.3 V GPIO inputs.
- Distributing 3.3 V and GND through breadboard power rails.
- Identifying and fixing split power rails.
- Using a multimeter to measure voltage, resistance, and continuity.
- Troubleshooting circuits by testing individual components.

One thing I've realised is that getting a circuit to work isn't always as simple as following a diagram.

A lot of my time has gone into figuring out why something isn't working, whether it's an incorrect GPIO connection, a sensor threshold that needs adjustment, a serial communication issue, or a breadboard connection I initially overlooked.

Working through these problems has helped me become more comfortable with debugging and understanding how the different parts of a circuit interact.
