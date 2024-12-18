#ifndef CARTLOADER_H
#define CARTLOADER_H

#include <fstream>
#include <memory>
#include <span>

#include "mem/imemorymanager.h"
#include "mem/mem_defines.h"

namespace gb {

class CartLoader {
public:
  CartLoader(const std::string& romFile, const std::string& ramFile);

  static size_t calculateNeccessarySize();
  std::vector<IMemoryManagerSP> constructBanks(std::span<uint8_t, std::dynamic_extent> buffer);

private:
  static constexpr address_type StartROM0 = 0x0000;
  static constexpr address_type EndROM0 = 0x3FFF;
  static constexpr address_type StartROM1 = 0x4000;
  static constexpr address_type EndROM1 = 0x7FFF;
  static constexpr address_type StartExtRAM = 0xA000;
  static constexpr address_type EndExtRAM = 0xBFFF;

  static constexpr size_t BankSize = 0x4000;

  static void read16K(std::span<uint8_t, BankSize> buffer, std::ifstream& file);

  std::ifstream romFile_;
  std::fstream ramFile_;
};

using CartLoaderUP = std::unique_ptr<CartLoader>;

} // namespace gb

#endif // CARTLOADER_H
