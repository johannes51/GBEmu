#ifndef PPUFACTORY_H
#define PPUFACTORY_H

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "ppu/ippu.h"

class PpuFactory {
public:
  explicit PpuFactory(IMemoryViewSP mem, IRegisterAdapterSP rIf)
      : mem_(std::move(mem))
      , if_(std::move(rIf))
  {
  }

  IPpuUP constructPpu();

private:
  IMemoryViewSP mem_;
  IRegisterAdapterSP if_;
};

#endif // PPUFACTORY_H
