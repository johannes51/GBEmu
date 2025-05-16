#ifndef IMEMORYVIEW_H
#define IMEMORYVIEW_H

#include <memory>

#include "defines.h"
#include "location16.h"
#include "location8.h"
#include "mem_defines.h"

class IMemoryView {
public:
  IMemoryView() = default;
  virtual ~IMemoryView() = default;
  DISABLE_COPY_AND_MOVE(IMemoryView)

  virtual Location8 getLocation8(const address_type address) = 0;
  virtual Location16 getLocation16(const address_type address) = 0;
};

using IMemoryViewUP = std::unique_ptr<IMemoryView>;

#endif // IMEMORYVIEW_H
