#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <vector>

#include "cpu/cpu_defines.h"
#include "gb_factories/peripheralregisterfactory.h"
#include "mem/imemoryview.h"
#include "peripherals/tickable.h"
#include "ppu/irenderer.h"

class SystemManager {
public:
  SystemManager(std::unique_ptr<Cpu> cpu, IMemoryViewUP mem, std::vector<TickableUP>&& peripherals,
      std::unordered_map<PeripheralRegisters, IRegisterAdapterUP>&& periRegisters, const GbPixelBuffer* pixBuffer,
      std::vector<uint8_t>&& memBuffer);
  DISABLE_COPY_AND_MOVE(SystemManager)
  ~SystemManager();

  void clock() const;
  const GbPixelBuffer* getPixBuffer() const;

private:
  CpuUP cpu_;
  IMemoryViewUP mem_;
  std::vector<TickableUP> peripherals_;
  std::unordered_map<PeripheralRegisters, IRegisterAdapterUP> periRegisters_;
  const GbPixelBuffer* pixBuffer_;
  std::vector<uint8_t> memBuffer_;
};

using SystemManagerUP = std::unique_ptr<SystemManager>;

#endif // SYSTEMMANAGER_H
