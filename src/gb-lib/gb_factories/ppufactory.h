#ifndef PPUFACTORY_H
#define PPUFACTORY_H

#include <memory>

#include "mem/mem_defines.h"

class Ppu;

class PpuFactory {
public:
  explicit PpuFactory(IMemoryViewSP ioBank)
      : ioBank_(std::move(ioBank))
  {
  }

  std::shared_ptr<Ppu> constructPpu();

private:
  IMemoryViewSP ioBank_;
};

#endif // PPUFACTORY_H
