#include "GXHTC3.h"

GXHTC3::GXHTC3(TwoWire *i2c) : _i2c(i2c), _crcCheck(true) {}

void GXHTC3::begin(int sda, int scl, uint32_t frequency) {
  _i2c->begin(sda, scl, frequency);
  sendCommand(CMD_SOFT_RESET);
}

void GXHTC3::wakeUp(void) { sendCommand(CMD_WAKEUP); }
void GXHTC3::sleep(void) { sendCommand(CMD_SLEEP); }
void GXHTC3::softReset(void) { sendCommand(CMD_SOFT_RESET); }
void GXHTC3::end() { _i2c->end(); }

uint16_t GXHTC3::readID() {
  uint8_t buff[3];
  sendCommand(CMD_READ_ID);
  bool success = receiveResponse(buff, sizeof(buff));

  if (!success || (_crcCheck && crc8(buff, 2) != buff[2])) return 0xFFFF;
  
  return (buff[0] << 8) | buff[1];
}

GXHTC3::Data GXHTC3::readData() {
  uint8_t buff[6];
  sendCommand(CMD_MEASURE_NORMAL_CS_RH_FIRST);
  bool success = receiveResponse(buff, sizeof(buff));

  if (!success ||
      (_crcCheck && (crc8(buff, 2) != buff[2] || crc8(&buff[3], 2) != buff[5])))
    return {NAN, NAN};

  uint16_t rawTemp = (buff[0] << 8) | buff[1];
  uint16_t rawHum = (buff[3] << 8) | buff[4];
  float temperature = 175.0f * rawTemp / 65535.0f - 45.0f;
  float humidity = 100.0f * rawHum / 65535.0f;

  return {temperature, humidity};
}

bool GXHTC3::receiveResponse(uint8_t *buff, size_t len) {
  if (_i2c->requestFrom(SENSOR_ADDRESS, len) != len) return false;
  for (size_t i = 0; i < len; ++i) {
    int value = _i2c->read();
    if (value < 0) return false;
    buff[i] = static_cast<uint8_t>(value);
  }
  return true;
}

void GXHTC3::sendCommand(uint16_t cmd) {
  _i2c->beginTransmission(SENSOR_ADDRESS);
  _i2c->write(static_cast<uint8_t>(cmd >> 8));
  _i2c->write(static_cast<uint8_t>(cmd & 0xFF));
  _i2c->endTransmission();
}

uint8_t GXHTC3::crc8(const uint8_t *data, size_t len) {
  uint8_t crc = 0xFF;
  for (size_t i = 0; i < len; ++i) {
    crc ^= data[i];
    for (uint8_t bit = 0; bit < 8; ++bit) {
      crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);
    }
  }
  return crc;
}