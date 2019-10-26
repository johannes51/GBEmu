#ifndef IMEMORYVIEW_H
#define IMEMORYVIEW_H

#include "location/location_defines.h"
#include "mem_defines.h"

class IMemoryView {
public:
  IMemoryView() = default;
  virtual ~IMemoryView() = default;
  DISABLE_COPY_AND_MOVE(IMemoryView)

  virtual Location<uint8_t> getByte(const address_type address) = 0;
  virtual Location<uint16_t> getWord(const address_type address) = 0;
};

#endif // IMEMORYVIEW_H
