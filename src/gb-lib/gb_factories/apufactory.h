#ifndef APUFACTORY_H
#define APUFACTORY_H

#include "apu/iapu.h"
#include "mem/imemoryview.h"

class ApuFactory {
public:
  explicit ApuFactory(IMemoryViewSP ioBank)
      : ioBank_(std::move(ioBank))
  {
  }

  IApuUP constructApu();

private:
  IMemoryViewSP ioBank_;
};

#endif // APUFACTORY_H
