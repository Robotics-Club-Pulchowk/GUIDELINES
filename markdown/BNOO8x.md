# Adafruit BNOO8x

Communication medium:
- I2C
- SPI
- UART

## Guide
### Code Setup

- Install `Adafruit_BNO08x` library in Arduino.

- Download code from [here](https://github.com/Robotics-Club-Pulchowk/Arduino_Codes/tree/main/bnoo8x).

- You need to `toggle defines` to change type of board and communication medium.
-  Adafruit uses magnetometer. So, initially yaw is not zero. To calibrate you can see [this](https://github.com/Robotics-Club-Pulchowk/Arduino_Codes/tree/main/bnoo8x_calibration).

### Circuit Setup

**Connection between BNOO8x and ESP32**:
-----------------------------
| BNOO8x   | ESP32          |
|----------|----------------|
| SCL      | GPIO 18 (SCK)  |
| SDA      | GPIO 19 (MISO) |
| DI       | GPIO 23 (MOSI) |
| CS       | GPIO 17        |
| RST      | GPIO 14        |
| INT      | GPIO 15        |
| P0       | GPIO 18        |
| P1       | GPIO 19        |
| 3V3      | 3V3            |
| GND      | GND            |
-----------------------------

**Connection between BNOO8x and PICO**:
-----------------------------
| BNOO8x   | PICO           |
|----------|----------------|
| SCL      | GPIO 18 (SCK)  |
| SDA      | GPIO 16 (MISO) |
| DI       | GPIO 19 (MOSI) |
| CS       | GPIO 5         |
| RST      | GPIO 21        |
| INT      | GPIO 22        |
| P0       | GPIO 25        |
| P1       | GPIO 26        |
| 3V3      | 3V3            |
| GND      | GND            |
-----------------------------

For pin loockup, see [this](https://github.com/Robotics-Club-Pulchowk/Arduino_Codes/tree/main/pin_loockup).

### Reference

- See https://learn.adafruit.com/adafruit-9-dof-orientation-imu-fusion-breakout-bno085/overview

- Also see https://www.ceva-ip.com/wp-content/uploads/2019/10/SH-2-SHTP-Reference-Manual.pdf

---
[Home](../README.md)