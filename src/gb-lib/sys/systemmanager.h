#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "cpu/cpu_defines.h"
#include "mem/mem_defines.h"

class SystemManager {
public:
  SystemManager(const IMemoryViewSP& memory);
  ~SystemManager();

  void clock() const;

  IMemoryViewSP memory_;
  CpuUP cpu_;
};

#endif // SYSTEMMANAGER_H
