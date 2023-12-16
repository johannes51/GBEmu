#include "cartloader.h"

#include <algorithm>
#include <cstring>

#include "mem/rambank.h"
#include "mem/rombank.h"

#include <array>

gb::CartLoader::CartLoader(const std::string& romFile)
    : romFile_(romFile, std::ios_base::in | std::ios_base::binary)
    , ramFile_()
{
}

gb::CartLoader::CartLoader(const std::string& romFile, const std::string& ramFile)
    : romFile_(romFile, std::ios_base::in | std::ios_base::binary)
    , ramFile_(ramFile, std::ios_base::in | std::ios_base::out | std::ios_base::binary)
{
}

auto gb::CartLoader::constructBanks() -> std::vector<IMemoryManagerSP>
{
  std::vector<IMemoryManagerSP> result;
  if (romFile_.fail()) {
    throw std::runtime_error("Could not open ROM file.");
  }
  auto buffer = read16K(romFile_);
  auto rom0 = std::make_shared<RomBank>(MemoryArea { StartROM0, EndROM0 }, std::move(buffer));
  buffer = read16K(romFile_);
  auto rom1 = std::make_shared<RomBank>(MemoryArea { StartROM1, EndROM1 }, std::move(buffer));
  result.push_back(rom0);
  result.push_back(rom1);
  result.push_back(std::make_shared<RamBank>(MemoryArea { StartExtRAM, EndExtRAM }));
  return result;
}

auto gb::CartLoader::read16K(std::ifstream& file) -> std::vector<uint8_t>
{
  static constexpr address_type Size = 0x4000;
  std::vector<uint8_t> result(Size);
  std::array<std::ifstream::char_type, Size> temp {};

  static_assert(sizeof(std::ifstream::char_type) == sizeof(uint8_t), "Non-portable if this doesn't hold");

  std::copy_n(std::istreambuf_iterator(file), Size * sizeof(std::ifstream::char_type), temp.begin());
  std::memcpy(result.data(), temp.data(), Size * sizeof(uint8_t));

  return result;
}
