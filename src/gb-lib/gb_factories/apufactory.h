#ifndef APUFACTORY_H
#define APUFACTORY_H

#include <vector>

#include "apu/apu.h"
#include "mem/imemoryview.h"

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
