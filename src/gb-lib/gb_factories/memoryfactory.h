#ifndef MEMORYFACTORY_H
#define MEMORYFACTORY_H

#include <vector>

#include "cartloader.h"
#include "mem/imemorymanager.h"
#include "mem/imemoryview.h"
#include "mem/memoryarea.h"

namespace gb {

class MemoryFactory {
public:
  MemoryFactory(CartLoaderUP&& romLoader, std::vector<uint8_t>& buffer);

  IMemoryViewSP constructMemoryLayout();

private:
  static constexpr MemoryArea VRAM = { 0x8000, 0x9FFF };
  static constexpr MemoryArea WRAM0 = { 0xC000, 0xCFFF };
  static constexpr MemoryArea WRAM1 = { 0xD000, 0xDFFF };
  static constexpr MemoryArea MIRROR_L = { 0xE000, 0xEFFF };
  static constexpr MemoryArea MIRROR_U = { 0xF000, 0xFDFF };
  static constexpr MemoryArea OAM = { 0xFE00, 0xFE9F };
  static constexpr MemoryArea NOT_USED = { 0xFEA0, 0xFEFF };
  static constexpr MemoryArea IO = { 0xFF00, 0xFF7F };
  static constexpr MemoryArea HRAM = { 0xFF80, 0xFFFE };
  static constexpr address_type IE = 0xFFFF;

  IMemoryManagerSP buildRamBank(MemoryArea area);
  static IMemoryManagerSP buildMirrorBank(MemoryArea mirrorArea, MemoryArea originArea, IMemoryManagerSP origin);
  static IMemoryManagerSP buildNullBank(MemoryArea area);
  std::vector<IMemoryManagerSP> buildCartBanks();
  static IMemoryManagerSP buildIe();

  CartLoaderUP loader_;
  std::vector<uint8_t>& buffer_;
  std::vector<uint8_t>::iterator ptr_;
};

} // namespace gb

#endif // MEMORYFACTORY_H
