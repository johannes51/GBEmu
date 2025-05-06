#include "cartloader.h"

#include <algorithm>
#include <cstring>

#include "mem/rambank.h"
#include "mem/rombank.h"

#include <array>

gb::CartLoader::CartLoader(const std::string& romFile, const std::string& ramFile)
    : romFile_(romFile, std::ios_base::in | std::ios_base::binary)
    , ramFile_(ramFile, std::ios_base::in | std::ios_base::out | std::ios_base::binary)
{
}

auto gb::CartLoader::calculateNeccessarySize() -> size_t // NOLINT(readability-convert-member-functions-to-static)
{
  return 3 * BankSize;
}

auto gb::CartLoader::constructBanks(std::span<uint8_t, std::dynamic_extent> buffer) -> std::vector<IMemoryManagerSP>
{
  std::vector<IMemoryManagerSP> result;
  if (romFile_.fail()) {
    throw std::runtime_error("Could not open ROM file.");
  }

  auto rom0Span = std::span<uint8_t, BankSize> { buffer.subspan(0, BankSize) };
  read16K(rom0Span, romFile_);
  auto rom0 = std::make_shared<RomBank>(MemoryArea { StartROM0, EndROM0 }, rom0Span);

  auto rom1Span = std::span<uint8_t, BankSize> { buffer.subspan(BankSize, BankSize) };
  read16K(rom1Span, romFile_);
  auto rom1 = std::make_shared<RomBank>(MemoryArea { StartROM1, EndROM1 }, rom1Span);

  auto ram0Span = std::span<uint8_t, BankSize> { buffer.subspan(BankSize, BankSize) };
  read16K(ram0Span, romFile_); // FIXME: this is a major bug
  auto ram0 = std::make_shared<RamBank>(MemoryArea { StartExtRAM, EndExtRAM }, ram0Span);

  result.push_back(rom0);
  result.push_back(rom1);
  result.push_back(ram0);

  return result;
}

void gb::CartLoader::read16K(std::span<uint8_t, BankSize> buffer, std::ifstream& file)
{
  std::array<std::ifstream::char_type, BankSize> temp {};

  static_assert(sizeof(std::ifstream::char_type) == sizeof(uint8_t), "Non-portable if this doesn't hold");

  std::copy_n(std::istreambuf_iterator(file), BankSize * sizeof(std::ifstream::char_type), temp.begin());
  std::memcpy(buffer.data(), temp.data(), BankSize * sizeof(uint8_t));
}
