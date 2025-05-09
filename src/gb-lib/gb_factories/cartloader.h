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

  size_t calculateNeccessarySize();
  std::vector<IMemoryManagerSP> constructBanks(std::span<uint8_t, std::dynamic_extent> buffer);

private:
  static constexpr size_t BankSize = 0x4000;

  static void read16K(std::span<uint8_t, BankSize> buffer, std::ifstream& file);

  std::ifstream romFile_;
  std::fstream ramFile_;
};

using CartLoaderUP = std::unique_ptr<CartLoader>;

} // namespace gb

#endif // CARTLOADER_H
