#ifndef APUFACTORY_H
#define APUFACTORY_H

#include "io/iobank.h"
#include "io/iregisteradapter.h"
#include "mem/imemoryview.h"

class Apu;

class ApuFactory {
public:
  explicit ApuFactory(IoBank& ioBank, IMemoryView& waveRam)
      : ioBank_(ioBank)
      , waveRam_(waveRam)
  {
  }

  std::unique_ptr<Apu> constructApu();

private:
  IoBank& ioBank_;
  IMemoryView& waveRam_;
};

#endif // APUFACTORY_H
