#ifndef GBFACTORY_H
#define GBFACTORY_H

#include <vector>

#include "cartloader.h"
#include "cpu/cpu_defines.h"
#include "mem/imemoryview.h"
#include "peripheralregisterfactory.h"
#include "peripherals/tickable.h"
#include "sys/systemmanager.h"

class GbFactory {
public:
  GbFactory(const std::string& romFile, const std::string& ramFile);
  DISABLE_COPY_AND_MOVE(GbFactory)

  SystemManagerUP constructSystem();

private:
  gb::CartLoaderUP cartLoader_;
  std::vector<uint8_t> buffer_;
  IMemoryViewSP mem_ = nullptr;
  IMemoryViewSP ioBank_ = nullptr;
  std::unique_ptr<PeripheralRegisterFactory> peripheralRF_ = nullptr;
  const IPixelBuffer* pixBuf_ = nullptr;

  void constructMemory();
  CpuUP constructCpu();
  std::vector<TickableSP> constructPeripherals();
};

#endif // GBFACTORY_H
