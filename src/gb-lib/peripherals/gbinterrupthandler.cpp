#include "gbinterrupthandler.h"

#include "cpu/operation/pushpop.h"
#include "cpu/registersinterface.h"

GbInterruptHandler::GbInterruptHandler(IRegisterAdapterSP rIf, IRegisterAdapterSP rIe)
    : if_(std::move(rIf))
    , ie_(std::move(rIe))
{
}

void GbInterruptHandler::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto p = PushPop { PushPop::Direction::Push, WordRegister::PC };
  p.execute(registers, memory);

  const auto selectedInterrupt = unmapInterrupt();

  if_->setBit(selectedInterrupt.first, false);
  *registers.get(WordRegister::PC) = selectedInterrupt.second;
}

auto GbInterruptHandler::isInterrupt() const -> bool
{
  return (ie_->get() & static_cast<uint8_t>(if_->get() & InterruptRegisterMask)) != 0U;
}

auto GbInterruptHandler::unmapInterrupt() -> std::pair<uint8_t, address_type>
{
  const auto activeInterrupts = ie_->get() & static_cast<uint8_t>(if_->get() & InterruptRegisterMask);
  for (const auto& bitAddressPair : HandlerAdresses) {
    if (checkInterruptBit(activeInterrupts, bitAddressPair.first)) {
      return bitAddressPair;
    }
  }
  throw std::invalid_argument("Invalid interrupt.");
}

auto GbInterruptHandler::checkInterruptBit(const uint8_t& activeInterrupts, const uint8_t pos) -> bool
{
  return (static_cast<uint8_t>(activeInterrupts >> pos) & 1U) == 1U;
}
