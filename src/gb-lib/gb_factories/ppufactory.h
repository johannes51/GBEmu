#ifndef PPUFACTORY_H
#define PPUFACTORY_H

#include <memory>

#include "mem/mem_defines.h"

class Ppu;

class PpuFactory {
public:
  explicit PpuFactory(IMemoryViewSP mem)
      : mem_(std::move(mem))
  {
  }

  std::shared_ptr<Ppu> constructPpu();

private:
  IMemoryViewSP mem_;
};

#endif // PPUFACTORY_H
