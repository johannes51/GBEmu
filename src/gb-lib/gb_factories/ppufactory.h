#ifndef PPUFACTORY_H
#define PPUFACTORY_H

#include "mem/imemoryview.h"
#include "mem/registers/iobank.h"
#include "mem/registers/iregisteradapter.h"
#include "ppu/ippu.h"

class PpuFactory {
public:
  explicit PpuFactory(IMemoryView& mem, IoBank& ioBank, IRegisterAdapter& rIf)
      : mem_(mem)
      , ioBank_(ioBank)
      , if_(rIf)
  {
  }

  IPpuUP constructPpu();

private:
  IMemoryView& mem_;
  IoBank& ioBank_;
  IRegisterAdapter& if_;
};

#endif // PPUFACTORY_H
