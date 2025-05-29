#ifndef PPUFACTORY_H
#define PPUFACTORY_H

#include "io/iobank.h"
#include "io/iregisteradapter.h"
#include "mem/imemoryview.h"
#include "ppu/ippu.h"

class PpuFactory {
public:
  explicit PpuFactory(IoBank& ioBank, IMemoryView& mem, IRegisterAdapter& rIf, IMemoryViewUP vram, IMemoryViewUP oam)
      : ioBank_(ioBank)
      , mem_(mem)
      , if_(rIf)
      , vram_(std::move(vram))
      , oam_(std::move(oam))
  {
  }

  IPpuUP constructPpu();

private:
  IoBank& ioBank_;
  IMemoryView& mem_;
  IRegisterAdapter& if_;
  IMemoryViewUP vram_;
  IMemoryViewUP oam_;
};

#endif // PPUFACTORY_H
