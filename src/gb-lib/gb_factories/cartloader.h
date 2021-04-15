#ifndef CARTLOADER_H
#define CARTLOADER_H

#include <fstream>
#include <vector>

#include "mem/mem_defines.h"

namespace gb {

class CartLoader {
public:
  CartLoader(const std::string& romFile);
  CartLoader(const std::string& romFile, const std::string& ramFile);

  std::vector<IMemoryManagerSP> constructBanks();

private:
  static constexpr address_type StartROM0 = 0x0000;
  static constexpr address_type EndROM0 = 0x3FFF;
  static constexpr address_type StartROM1 = 0x4000;
  static constexpr address_type EndROM1 = 0x7FFF;
  static constexpr address_type StartExtRAM = 0xA000;
  static constexpr address_type EndExtRAM = 0xBFFF;

  static std::vector<uint8_t> read16K(std::ifstream& file);

  std::ifstream romFile_;
  std::fstream ramFile_;
};

} // namespace gb

#endif // CARTLOADER_H
