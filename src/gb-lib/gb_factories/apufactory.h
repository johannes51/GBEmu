#ifndef APUFACTORY_H
#define APUFACTORY_H

#include "mem/mem_defines.h"
#include "peripherals/peri_defines.h"

class ApuFactory {
public:
  explicit ApuFactory(IMemoryViewSP ioBank)
      : ioBank_(std::move(ioBank))
  {
  }

  PeripheralSP constructApu();

private:
  IMemoryViewSP ioBank_;
};

#endif // APUFACTORY_H
