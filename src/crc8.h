#ifndef CRC8_H
#define CRC8_H
#include <stdint.h>
#include <cstddef>

// CRC-8 polynomial: x^8 + x^5 + x^4 + 1
uint8_t crc8(const uint8_t *data, size_t len);

#endif  // CRC8_H

