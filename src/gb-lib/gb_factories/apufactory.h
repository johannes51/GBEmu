#ifndef APUFACTORY_H
#define APUFACTORY_H

#include "apu/iapu.h"
#include "mem/imemoryview.h"
#include "mem/registers/iobank.h"
#include "mem/registers/iregisteradapter.h"

class ApuFactory {
public:
  explicit ApuFactory(IoBank& ioBank, IMemoryView& waveRam, IRegisterAdapterUP div_apu)
      : ioBank_(ioBank)
      , waveRam_(waveRam)
      , div_apu_(std::move(div_apu))
  {
  }

  IApuUP constructApu();

private:
  IoBank& ioBank_;
  IMemoryView& waveRam_;
  IRegisterAdapterUP div_apu_;
};

#endif // APUFACTORY_H
