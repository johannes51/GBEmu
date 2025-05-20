#ifndef MEMORYFACTORY_H
#define MEMORYFACTORY_H

#include <vector>

#include "cartloader.h"
#include "mem/imemorymanager.h"
#include "mem/imemoryview.h"
#include "mem/memoryarea.h"

class IoBank;
class SingleRegisterBank;

namespace gb {

class MemoryFactory {
public:
  MemoryFactory(CartLoaderUP romLoader, std::vector<uint8_t>& buffer);

  IoBank* getIoBank();
  SingleRegisterBank* getIeBank();
  IMemoryViewUP releaseMemory();

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

  IMemoryViewUP constructMemoryLayout();
  IMemoryManagerUP buildRamBank(MemoryArea area);
  std::unique_ptr<IoBank> buildIoBank(MemoryArea area);
  std::vector<IMemoryManagerUP> buildCartBanks();

  CartLoaderUP loader_;
  std::vector<uint8_t>& buffer_;
  std::vector<uint8_t>::iterator ptr_;
  IoBank* ioBank_ = nullptr;
  SingleRegisterBank* ieBank_ = nullptr;
  IMemoryViewUP mem_ = nullptr; // initialize mem_ last because constructMemoryLayout() needs the other members
};

} // namespace gb

#endif // MEMORYFACTORY_H
