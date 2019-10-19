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
    buffer = read16K(romFile_);
    auto rom1 = std::make_shared<RomBank>(MemoryArea{ StartROM1, EndROM1 }, std::move(buffer));
    result.push_back(rom0);
    result.push_back(rom1);
  }
  return result;
}

std::vector<uint8_t> gb::CartLoader::read16K(std::ifstream& file)
{
  file.unsetf(std::ios::skipws);
  static constexpr address_type Size = 0x4000;
  std::vector<uint8_t> result{};
  result.resize(Size);
  auto it = std::istream_iterator<uint8_t>{file};
  for (int pos = 0; pos < Size; ++pos) {
    if (it == std::istream_iterator<uint8_t>{}) {
      break;
    }
    result.at(pos) = *it;
    ++it;
  }

  return result;
}
