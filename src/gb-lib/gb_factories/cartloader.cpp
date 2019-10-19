#include "cartloader.h"

#include <iterator>

#include "mem/rombank.h"

gb::CartLoader::CartLoader(std::ifstream&& romFile, std::basic_fstream<uint8_t>&& ramFile)
  : romFile_(std::move(romFile))
  , ramFile_(std::move(ramFile))
{
}

std::vector<IMemoryManagerSP> gb::CartLoader::constructBanks()
{
  std::vector<IMemoryManagerSP> result;
  if (romFile_.good()) {
    auto buffer = read16K(romFile_);
    auto rom0 = std::make_shared<RomBank>(MemoryArea{ StartROM0, EndROM0 }, std::move(buffer));
    result.push_back(rom0);
  }
  return result;
}

std::vector<uint8_t> gb::CartLoader::read16K(std::ifstream& file)
{
  static constexpr address_type Size = 0x3FFF;
  file.unsetf(std::ios::skipws);
  std::vector<uint8_t> result{std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>()};

  return result;
}
