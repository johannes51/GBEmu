#include "cartloader.h"

#include "mbcbankfactory.h"
#include "mem/ram/rambank.h"
#include "mem/rom/rombank.h"

#include <array>

constexpr address_type StartROM0 = 0x0000;
constexpr address_type EndROM0 = 0x3FFF;
constexpr address_type StartROM1 = 0x4000;
constexpr address_type EndROM1 = 0x7FFF;
constexpr address_type StartExtRAM = 0xA000;
constexpr address_type EndExtRAM = 0xBFFF;

auto countBanks(uint8_t romSize) -> uint8_t { return 2U * (1U << romSize); }

gb::CartLoader::CartLoader(const std::string& romFile, const std::string& ramFile)
    : romFile_(romFile, std::ios_base::in | std::ios_base::binary)
    , ramFile_(ramFile, std::ios_base::in | std::ios_base::out | std::ios_base::binary)
    , topBuffer_()
{
  if (romFile_.fail()) {
    throw std::runtime_error("Could not open ROM file.");
  }

  read<TopSize>(topBuffer_, romFile_);
}

auto gb::CartLoader::calculateNeccessarySize() -> size_t // NOLINT(readability-convert-member-functions-to-static)
{
  const auto romSize = topBuffer_.at(RomSizeAddress);
  if (romSize > RomSizeMax) {
    throw std::invalid_argument("ROM file header has invalid size parameter.");
  }

  return (RomBankSize * countBanks(romSize)) + RamBankSize /* 1 RAM bank for now */;
}

auto gb::CartLoader::constructCart(std::span<uint8_t, std::dynamic_extent> buffer) -> CartUP
{
  size_t accumulatedAdress = 0U;

  auto rom0Span = std::span<uint8_t, RomBankSize> { buffer.subspan(accumulatedAdress, RomBankSize) };
  accumulatedAdress += rom0Span.size();
  std::copy_n(topBuffer_.begin(), TopSize, rom0Span.begin());
  read<RomBankSize - TopSize>(rom0Span.subspan<TopSize, RomBankSize - TopSize>(), romFile_);
  auto rom0 = std::make_unique<RomBank>(MemoryArea { StartROM0, EndROM0 }, rom0Span);

  std::vector<RomBankUP> banks;
  const auto banksToFill = countBanks(topBuffer_.at(RomSizeAddress));
  for (auto banksFilled = 1U; banksFilled < banksToFill; ++banksFilled) {
    auto romSpan = std::span<uint8_t, RomBankSize> { buffer.subspan(accumulatedAdress, RomBankSize) };
    accumulatedAdress += romSpan.size();
    read<RomBankSize>(romSpan, romFile_);
    banks.push_back(std::make_unique<RomBank>(MemoryArea { StartROM1, EndROM1 }, romSpan));
  }

  auto ram0Span = std::span<uint8_t, RamBankSize> { buffer.subspan(accumulatedAdress, RamBankSize) };
  read<RamBankSize>(ram0Span, romFile_); // FIXME: this is a major bug
  auto ram0 = std::make_unique<RamBank>(MemoryArea { StartExtRAM, EndExtRAM }, ram0Span);

  return std::make_unique<Cart>(MbcBankFactory::constructMbcBank(
      topBuffer_.at(MbcTypeAddress), std::move(rom0), std::move(banks), std::move(ram0)));
}
