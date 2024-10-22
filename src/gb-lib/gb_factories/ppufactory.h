#ifndef PPUFACTORY_H
#define PPUFACTORY_H

#include "mem/imemoryview.h"
#include "peripherals/peri_defines.h"

class PpuFactory {
public:
  explicit PpuFactory(IMemoryViewSP mem)
      : mem_(std::move(mem))
  {
  }

  PeripheralSP constructPpu();

private:
  IMemoryViewSP mem_;
};

#endif // PPUFACTORY_H
