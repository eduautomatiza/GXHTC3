# GXHTC3 - Arduino Library for Temperature and Humidity Sensor

**GXHTC3** is an Arduino-compatible library for interfacing with the GXHTC3 temperature and humidity sensor via I2C. It provides an easy-to-use interface for sensor communication, data reading, and power management.

## Features

- Read temperature and humidity with optional CRC check
- Read the sensor's unique ID
- Control sleep, wake-up, and soft reset
- Support for custom `TwoWire` instances (e.g., `Wire1`)

## Installation

1. Download or clone this repository.
2. Copy `GXHTC3.h` and `GXHTC3.cpp` into your Arduino project or library folder.

## Example

```cpp
#include <Wire.h>
#include "GXHTC3.h"

GXHTC3 sensor;

void setup() {
  Serial.begin(115200);
  sensor.begin();      // Initialize I2C and reset the sensor
  sensor.wakeUp();     // Wake up the sensor
}

void loop() {
  auto data = sensor.readData();
  if (!isnan(data.temperature) && !isnan(data.humidity)) {
    Serial.print("Temperature: ");
    Serial.print(data.temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(data.humidity);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read sensor data.");
  }
  delay(2000);
}
```

## License

MIT License
