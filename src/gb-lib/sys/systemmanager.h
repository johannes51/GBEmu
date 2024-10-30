#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <vector>

#include "cpu/cpu_defines.h"
#include "ppu/irenderer.h"

#include "peripherals/tickable.h"

class SystemManager {
public:
  SystemManager(std::unique_ptr<Cpu> cpu, std::vector<TickableSP> peripherals, const IPixelBuffer* buffer);
  DISABLE_COPY_AND_MOVE(SystemManager)
  ~SystemManager();

  void clock() const;
  const IPixelBuffer* getBuffer() const;

private:
  CpuUP cpu_;
  std::vector<TickableSP> peripherals_;
  const IPixelBuffer* buffer_;
};

using SystemManagerUP = std::unique_ptr<SystemManager>;

#endif // SYSTEMMANAGER_H
