#include "mbc1.h"

#include "mem/common/mem_tools.h"
#include "mem/rest/onelocation.h"

const std::vector<MemoryArea> Mbc1::RomMemoryAreas
    = { { .from = 0x0000U, .to = 0x3FFFU }, { .from = 0x4000U, .to = 0x7FFFU }, { .from = 0xA000U, .to = 0xBFFFU } };

Mbc1::Mbc1(RomBankUP rom0, std::vector<RomBankUP>&& rom1Banks, IMemoryViewUP ram0)
    : rom0_(std::move(rom0))
    , rom1Banks_(std::move(rom1Banks))
    , ram0_(std::move(ram0))
    , selectedRomBank_()
    , ramEnabled_(false)
    , bankingMode_(BankingMode::Rom)
    , romBankNumber_(0U)
    , ramBankNumber_(0U)
{
  updateSelectedRomBank();
  updateSelectedRamBank();
  rom0_->setMbc(this);
}

auto Mbc1::getLocation8(const address_type address) -> ILocation8&
{
  if (mem_tools::isSafe(address, RomMemoryAreas[0U])) {
    return rom0_->getLocation8(address);
  } else if (mem_tools::isSafe(address, RomMemoryAreas[1U])) {
    return (*selectedRomBank_)->getLocation8(address);
  } else if (mem_tools::isSafe(address, RomMemoryAreas[2U])) {
    return ramEnabled_ ? ram0_->getLocation8(address) : OneLocation::instance();
  } else {
    throw std::logic_error("Out of cart bounds");
  }
}

void Mbc1::handleWrite(const address_type address, const uint8_t value)
{
  if (address <= RamEnableTop) {
    ramEnabled_ = (value & RamEnableMask) != 0;
  } else if (address <= RomBankNumberTop) {
    romBankNumber_ = static_cast<unsigned>(romBankNumber_ & static_cast<unsigned>(~RomBankNumberMask))
        | static_cast<unsigned>(value & RomBankNumberMask);
  } else if (address <= RamRomHBankNumberTop) {
    if (bankingMode_ == BankingMode::Rom) {
      romBankNumber_ = static_cast<unsigned>(romBankNumber_ & RomBankNumberMask)
          | static_cast<unsigned>(static_cast<unsigned>(value & RamRomHBankNumberMask) << RomHBankShift);
      updateSelectedRomBank();
    } else /*if (bankingMode_ == BankingMode::Ram)*/ {
      ramBankNumber_ = value & RamRomHBankNumberMask;
      updateSelectedRamBank();
    }
  } else if (address <= RomRamModeTop) {
    bankingMode_ = (value == 0U) ? BankingMode::Rom : BankingMode::Ram;
  } else {
    throw std::invalid_argument { "Write in wrong MBC area: " + std::to_string(address) };
  }
}

void Mbc1::updateSelectedRomBank()
{
  const auto actualRomBank = ((romBankNumber_ > 0U) ? romBankNumber_ - 1U : 0U) % rom1Banks_.size();
  selectedRomBank_ = rom1Banks_.begin();
  std::advance(selectedRomBank_, actualRomBank);
  (*selectedRomBank_)->setMbc(this);
}

void Mbc1::updateSelectedRamBank()
{
  // Not implemented, do nothing
}
