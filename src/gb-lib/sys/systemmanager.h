#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <vector>

#include "cart/cart.h"
#include "mem/imemoryview.h"
#include "peripherals/tickable.h"
#include "ppu/irenderer.h"

class Cpu;

class SystemManager {
public:
  SystemManager(std::unique_ptr<Cpu> cpu, IMemoryViewUP mem, CartUP cart, std::vector<TickableUP>&& peripherals,
      const GbPixelBuffer* pixBuffer, std::vector<uint8_t>&& memBuffer);
  DISABLE_COPY_AND_MOVE(SystemManager)
  ~SystemManager();

  void clock() const;
  const GbPixelBuffer* getPixBuffer() const;

private:
  std::unique_ptr<Cpu> cpu_;
  IMemoryViewUP mem_;
  CartUP cart_;
  std::vector<TickableUP> peripherals_;
  const GbPixelBuffer* pixBuffer_;
  std::vector<uint8_t> memBuffer_;
};

using SystemManagerUP = std::unique_ptr<SystemManager>;

#endif // SYSTEMMANAGER_H
