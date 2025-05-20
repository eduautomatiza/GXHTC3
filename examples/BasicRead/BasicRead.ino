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
