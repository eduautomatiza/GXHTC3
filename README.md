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
3. Open the Arduino IDE and select one of the examples from **File > Examples > GXHTC3**.

## Examples

### 🧪 BasicRead

This example demonstrates a minimal usage of the GXHTC3 sensor using default I2C pins and CRC validation enabled (default behavior):

```cpp
#include <Wire.h>
#include <GXHTC3.h>

GXHTC3 sensor;

void setup() {
  Serial.begin(115200);
  sensor.begin();
  sensor.wakeUp();
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

📁 File: `examples/BasicRead/BasicRead.ino`

---

### 🔧 CustomPinsNoCRC

This example demonstrates how to use custom I2C pins and disable CRC checking to improve performance (e.g., on ESP32 with `Wire1`):

```cpp
#include <Wire.h>
#include <GXHTC3.h>

TwoWire customWire = TwoWire(1);
GXHTC3 sensor(&customWire);

void setup() {
  Serial.begin(115200);
  sensor.begin(21, 22, 400000); // Custom pins, 400kHz
  sensor.setCrcCheck(false);   // Disable CRC check
  sensor.wakeUp();
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
    Serial.println("Invalid reading (possibly due to I2C issue).");
  }
  delay(1000);
}
```

📁 File: `examples/CustomPinsNoCRC/CustomPinsNoCRC.ino`

---

## API Reference

### Public Methods

| Method                          | Description |
|---------------------------------|-------------|
| `begin(int sda, int scl, uint32_t frequency)` | Initializes the I2C bus (optional pins and frequency) |
| `end()`                         | Ends the I2C communication |
| `readData()`                    | Returns temperature and humidity as a `Data` struct |
| `readID()`                      | Reads and returns the 16-bit sensor ID |
| `wakeUp()`                      | Sends wake-up command |
| `sleep()`                       | Puts the sensor in sleep mode |
| `softReset()`                   | Sends soft reset command |
| `setCrcCheck(bool enable)`      | Enables or disables CRC validation |

### `Data` Struct

```cpp
struct Data {
  float temperature;
  float humidity;
};
```

## Notes

- The sensor's I2C address is fixed at `0x70`.
- Commands are based on the GXHTC3 datasheet.
- CRC8 check is enabled by default and can be disabled via `setCrcCheck(false)`.

## License

MIT License
