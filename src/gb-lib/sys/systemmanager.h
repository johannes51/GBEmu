#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <vector>

#include "cpu/cpu_defines.h"
#include "mem/mem_defines.h"
#include "peripherals/peri_defines.h"

class SystemManager {
public:
  SystemManager(IMemoryViewSP memory, std::unique_ptr<Cpu> cpu, std::vector<PeripheralSP> peripherals);
  ~SystemManager();

  void clock() const;

  IMemoryViewSP memory_;
  CpuUP cpu_;
  std::vector<PeripheralSP> peripherals_;
};

#endif // SYSTEMMANAGER_H
