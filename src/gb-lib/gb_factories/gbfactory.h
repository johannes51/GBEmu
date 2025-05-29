#ifndef GBFACTORY_H
#define GBFACTORY_H

#include <vector>

#include "cartloader.h"
#include "io/iobank.h"
#include "io/iregisteradapter.h"
#include "mem/imemorywordview.h"
#include "peripherals/tickable.h"
#include "sys/systemmanager.h"

class SingleRegisterBank;

class GbFactory {
public:
  GbFactory(const std::string& romFile, const std::string& ramFile);
  DISABLE_COPY_AND_MOVE(GbFactory)

  SystemManagerUP constructSystem();

private:
  CartUP buildCart(const std::string& romFile, const std::string& ramFile);
  IMemoryWordViewUP constructMemory();
  std::unique_ptr<Cpu> constructCpu();
  std::vector<TickableUP> constructPeripherals();
  TickableUP constructTimer(IRegisterAdapter& divApu);
  TickableUP constructJoypad();
  TickableUP constructSerial();
  TickableUP constructOamDma();

  std::vector<uint8_t> buffer_;
  CartUP cart_;
  IoBank* ioBank_;
  IMemoryViewUP vram_;
  IMemoryViewUP oam_;
  IMemoryWordViewUP mem_; // construct last because other members are written by this

  IRegisterAdapter* if_ = nullptr;
  const GbPixelBuffer* pixBuf_ = nullptr;
};

#endif // GBFACTORY_H
