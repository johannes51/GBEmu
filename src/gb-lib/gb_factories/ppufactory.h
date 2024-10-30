#ifndef PPUFACTORY_H
#define PPUFACTORY_H

#include "mem/imemoryview.h"
#include "ppu/ippu.h"

class PpuFactory {
public:
  explicit PpuFactory(IMemoryViewSP mem)
      : mem_(std::move(mem))
  {
  }

  IPpuUP constructPpu();

private:
  IMemoryViewSP mem_;
};

#endif // PPUFACTORY_H
