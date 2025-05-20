#ifndef __GXHTC3_H__
#define __GXHTC3_H__

#include <Arduino.h>
#include <Wire.h>

class GXHTC3 {
 public:
  struct Data {
    float temperature;
    float humidity;
  };

  explicit GXHTC3(TwoWire *i2c = &Wire);

  void begin(int sda = -1, int scl = -1, uint32_t frequency = 0);
  void end();

  Data readData();
  uint16_t readID();
  void wakeUp(void);
  void sleep(void);
  void softReset(void);

  void setCrcCheck(bool enable) { _crcCheck = enable; }

 private:
  static constexpr uint8_t SENSOR_ADDRESS = 0x70;
  static constexpr uint16_t CMD_READ_ID = 0xEFC8;
  static constexpr uint16_t CMD_WAKEUP = 0x3517;
  static constexpr uint16_t CMD_MEASURE_NORMAL_CS_RH_FIRST = 0x7CA2;
  static constexpr uint16_t CMD_SLEEP = 0xB098;
  static constexpr uint16_t CMD_SOFT_RESET = 0x805D;

  TwoWire *_i2c;
  bool _crcCheck;

  void sendCommand(uint16_t cmd);
  bool receiveResponse(uint8_t *buff, size_t len);
};

#endif
