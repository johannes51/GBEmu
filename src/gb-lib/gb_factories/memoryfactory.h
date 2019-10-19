#ifndef GBMEMORY_H
#define GBMEMORY_H

#include <vector>

#include "mem/mem_defines.h"
#include "gb_defines.h"


namespace gb {

class MemoryFactory
{
public:
  MemoryFactory(RomLoaderUP&& romLoader);

  IMemoryViewSP constructMemoryLayout();

private:
  static constexpr MemoryArea WRAM0 = { 0xC000, 0xCFFF };
  static constexpr MemoryArea WRAM1 = { 0xD000, 0xDFFF };
  static constexpr MemoryArea MIRROR_L = { 0xE000, 0xEFFF };
  static constexpr MemoryArea MIRROR_U = { 0xF000, 0xFDFF };
  static constexpr MemoryArea NOT_USED = { 0xFEA0, 0xFEFF };
  static constexpr MemoryArea HRAM = { 0xFF80, 0xFFFE };

  IMemoryManagerSP buildRamBank(MemoryArea area);
  IMemoryManagerSP buildMirrorBank(MemoryArea mirrorArea, MemoryArea originArea, IMemoryManagerSP origin);
  IMemoryManagerSP buildNullBank(MemoryArea area);
  std::vector<IMemoryManagerSP> buildCartBanks();

  RomLoaderUP loader_;
};

} // namespace gb

#endif // GBMEMORY_H
