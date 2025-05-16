#include "cartloader.h"

#include <algorithm>
#include <cstring>

#include "mem/ram/rambank.h"
#include "mem/rom/rombank.h"

#include <array>

constexpr address_type StartROM0 = 0x0000;
constexpr address_type EndROM0 = 0x3FFF;
constexpr address_type StartROM1 = 0x4000;
constexpr address_type EndROM1 = 0x7FFF;
constexpr address_type StartExtRAM = 0xA000;
constexpr address_type EndExtRAM = 0xBFFF;

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

  auto ram0Span = std::span<uint8_t, BankSize> { buffer.subspan(2 * BankSize, BankSize) };
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
