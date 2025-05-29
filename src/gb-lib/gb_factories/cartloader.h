#ifndef CARTLOADER_H
#define CARTLOADER_H

#include <algorithm>
#include <cstring>
#include <fstream>
#include <memory>
#include <span>

#include "cart/cart.h"
#include "mem/imemoryview.h"
#include "mem/mem_defines.h"

namespace gb {

class CartLoader {
public:
  CartLoader(const std::string& romFile, const std::string& ramFile);

  size_t calculateNeccessarySize();
  CartUP constructCart(std::span<uint8_t, std::dynamic_extent> buffer);

private:
  static constexpr size_t RomBankSize = 0x4000U;
  static constexpr size_t RamBankSize = 0x2000U;
  static constexpr size_t TopSize = 0x0150U;
  static constexpr uint8_t RomSizeMax = 0x08U;
  static constexpr address_type MbcTypeAddress = 0x0147U;
  static constexpr address_type RomSizeAddress = 0x0148U;
  static constexpr address_type RamSizeAddress = 0x0149U;

  template <size_t BufferSize> void read(std::span<uint8_t, BufferSize> buffer, std::ifstream& file);

  std::ifstream romFile_;
  std::fstream ramFile_;
  std::array<uint8_t, TopSize> topBuffer_;
};

template <size_t BufferSize> inline void CartLoader::read(std::span<uint8_t, BufferSize> buffer, std::ifstream& file)
{
  std::array<std::ifstream::char_type, BufferSize> temp {};

  static_assert(sizeof(std::ifstream::char_type) == sizeof(uint8_t), "Non-portable if this doesn't hold");

  std::copy_n(std::istreambuf_iterator(file), BufferSize * sizeof(std::ifstream::char_type), temp.begin());
  std::memcpy(buffer.data(), temp.data(), BufferSize * sizeof(uint8_t));
}

} // namespace gb

#endif // CARTLOADER_H
