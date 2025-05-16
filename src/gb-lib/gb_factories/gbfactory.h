#ifndef GBFACTORY_H
#define GBFACTORY_H

#include <vector>

#include "cartloader.h"
#include "cpu/cpu_defines.h"
#include "mem/imemoryview.h"
#include "peripheralregisterfactory.h"
#include "peripherals/tickable.h"
#include "sys/systemmanager.h"

class SingleRegisterBank;

class GbFactory {
public:
  GbFactory(const std::string& romFile, const std::string& ramFile);
  DISABLE_COPY_AND_MOVE(GbFactory)

  SystemManagerUP constructSystem();

private:
  void constructMemory();
  CpuUP constructCpu();
  std::vector<TickableSP> constructPeripherals();
  TickableSP constructTimer();

  gb::CartLoaderUP cartLoader_;
  std::vector<uint8_t> buffer_;
  IMemoryViewUP mem_ = nullptr;
  IoBank* ioBank_ = nullptr;
  SingleRegisterBank* ieBank_ = nullptr;
  std::unique_ptr<PeripheralRegisterFactory> peripheralRF_ = nullptr;
  const GbPixelBuffer* pixBuf_ = nullptr;
};

#endif // GBFACTORY_H
