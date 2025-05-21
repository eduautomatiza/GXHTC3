#include <Wire.h>
#include <GXHTC3.h>

// Using custom SDA and SCL pins on Wire1 (ESP32, etc)
TwoWire customWire = TwoWire(1);
GXHTC3 sensor(&customWire);

void setup() {
  Serial.begin(115200);

  // Begin with custom pins (GPIO 21 and 22) and 400kHz I2C frequency
  sensor.begin(21, 22, 400000);

  // Optional: disable CRC checking for performance
  sensor.setCrcCheck(false);

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
