#ifndef IMEMORYVIEW_H
#define IMEMORYVIEW_H

#include "defines.h"
#include "location/location.h"
#include "mem_defines.h"

class IMemoryView {
public:
  IMemoryView() = default;
  virtual ~IMemoryView() = default;
  DISABLE_COPY_AND_MOVE(IMemoryView)

  virtual LocationUP getLocation(const address_type address, bool tryWord = false) = 0;
};

#endif // IMEMORYVIEW_H
