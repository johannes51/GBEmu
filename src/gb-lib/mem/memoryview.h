#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include <stdint.h>
#include <vector>

#include "mem_defines.h"
#include "util/util_defines.h"


class MemoryView
{
public:
  virtual ~MemoryView() = default;

  virtual LocationUP<uint8_t> getByte(address_type address) = 0;
  virtual LocationUP<uint16_t> getWord(address_type address) = 0;
};

#endif // MEMORYVIEW_H

