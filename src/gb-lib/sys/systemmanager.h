#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <vector>

#include "cpu/cpu_defines.h"
#include "mem/imemoryview.h"

#include "apu/iapu.h"
#include "input/joypad.h"
#include "ppu/ippu.h"

class SystemManager {
public:
  SystemManager(IMemoryViewSP memory, std::unique_ptr<Cpu> cpu, IApuUP apu, IPpuUP ppu, JoypadUP joypad);
  ~SystemManager();

  void clock() const;

  IMemoryViewSP memory_;
  CpuUP cpu_;
  JoypadUP joypad_;
  IApuUP apu_;
  IPpuUP ppu_;
};

#endif // SYSTEMMANAGER_H
