#include "mbcbankfactory.h"

#include "cart/mbc1.h"
#include "cart/nombc.h"

auto MbcBankFactory::constructMbcBank(const uint8_t cartridgeType, RomBankUP rom0, std::vector<RomBankUP>&& rom1Banks,
    IMemoryViewUP ram0) -> IMemoryViewUP
{
  switch (cartridgeType) {
  case 0x00U:
    return std::make_unique<NoMbc>(std::move(rom0), std::move(rom1Banks[0U]));
    break;
  case 0x01U:
  case 0x02U:
  case 0x03U:
    return std::make_unique<Mbc1>(std::move(rom0), std::move(rom1Banks), std::move(ram0));
    break;
  default:
    throw std::invalid_argument("Only MBC1 implemented at this point.");
    break;
  }
}
