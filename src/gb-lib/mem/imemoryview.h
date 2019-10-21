#ifndef IMEMORYVIEW_H
#define IMEMORYVIEW_H

#include <stdint.h>

#include "location/location_defines.h"
#include "mem_defines.h"

class IMemoryView {
public:
  virtual ~IMemoryView() = default;

  virtual LocationUP<uint8_t> getByte(address_type address) = 0;
  virtual LocationUP<uint16_t> getWord(address_type address) = 0;
};

#endif // IMEMORYVIEW_H
