#ifndef IMEMORYVIEW_H
#define IMEMORYVIEW_H

#include "location/location_defines.h"
#include "mem_defines.h"

class IMemoryView {
public:
  virtual ~IMemoryView() = default;

  virtual LocationUP<uint8_t> getByte(const address_type address) = 0;
  virtual LocationUP<uint16_t> getWord(const address_type address) = 0;
};

#endif // IMEMORYVIEW_H
