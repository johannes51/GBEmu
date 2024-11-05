#ifndef APUFACTORY_H
#define APUFACTORY_H

#include "apu/iapu.h"
#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

class ApuFactory {
public:
  explicit ApuFactory(IMemoryViewSP mem, IRegisterAdapterSP div_apu)
      : mem_(std::move(mem))
      , div_apu_(div_apu)
  {
  }

  IApuUP constructApu();

private:
  IMemoryViewSP mem_;
  IRegisterAdapterSP div_apu_;
};

#endif // APUFACTORY_H
