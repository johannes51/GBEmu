#include "cartloader.h"

#include "mem/rombank.h"

gb::CartLoader::CartLoader(std::ifstream &&romFile, std::fstream &&ramFile)
    : romFile_(std::move(romFile)), ramFile_(std::move(ramFile)) {
  romFile_.unsetf(std::ios::skipws);
  ramFile_.unsetf(std::ios::skipws);
}

std::vector<IMemoryManagerSP> gb::CartLoader::constructBanks() {
  std::vector<IMemoryManagerSP> result;
  if (romFile_.good()) {
    auto buffer = read16K(romFile_);
    auto rom0 = std::make_shared<RomBank>(MemoryArea{StartROM0, EndROM0},
                                          std::move(buffer));
    buffer = read16K(romFile_);
    auto rom1 = std::make_shared<RomBank>(MemoryArea{StartROM1, EndROM1},
                                          std::move(buffer));
    result.push_back(rom0);
    result.push_back(rom1);
  }
  return result;
}

std::vector<uint8_t> gb::CartLoader::read16K(std::ifstream &file) {
  static constexpr address_type Size = 0x4000;
  std::vector<uint8_t> result(Size);

  file.read(reinterpret_cast<char *>(result.data()), Size * sizeof(uint8_t));

  return result;
}
