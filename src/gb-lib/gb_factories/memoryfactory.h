#ifndef MEMORYFACTORY_H
#define MEMORYFACTORY_H

#include <span>

#include "io/iobank.h"
#include "mem/imemorywordview.h"
#include "mem/mem_defines.h"

namespace gb {

class MemoryFactory final {
public:
  explicit MemoryFactory(IMemoryView& cartBanks, IoBankUP ioBank, std::span<uint8_t, std::dynamic_extent> buffer);
  DISABLE_COPY_AND_MOVE(MemoryFactory)

  IMemoryViewUP releaseVram();
  IMemoryViewUP releaseOam();
  IMemoryWordViewUP releaseMemory();

  static size_t getSize();

  static constexpr MemoryArea VRAM = { 0x8000U, 0x9FFFU };
  static constexpr MemoryArea WRAM = { 0xC000U, 0xDFFFU };
  static constexpr MemoryArea MIRROR = { 0xE000U, 0xFDFFU };
  static constexpr MemoryArea OAM = { 0xFE00U, 0xFE9FU };
  static constexpr MemoryArea NOT_USED = { 0xFEA0U, 0xFEFFU };
  static constexpr MemoryArea IO = { 0xFF00U, 0xFF7FU };
  static constexpr MemoryArea HRAM = { 0xFF80U, 0xFFFEU };
  static constexpr address_type IE = 0xFFFFU;

private:
  IMemoryWordViewUP constructMemoryLayout();
  IMemoryViewUP buildRamBank(MemoryArea area);

  std::span<uint8_t, std::dynamic_extent> buffer_;
  std::span<uint8_t>::iterator ptr_;

  IMemoryView& cartBanks_;
  IoBankUP ioBank_;
  IMemoryViewUP vram_;
  IMemoryViewUP oam_;
  IMemoryWordViewUP mem_; // initialize mem_ last because constructMemoryLayout() needs the other members
};

} // namespace gb

#endif // MEMORYFACTORY_H
