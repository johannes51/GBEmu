#include "divregister.h"

DivRegister::DivRegister(IMemoryViewSP mem)
    : MemoryRegisterAdapter(std::move(mem), DivRegisterAdress)
{
}

void DivRegister::set(uint8_t value)
{
  (void)value;
  systemTimer_ = 0U;
  MemoryRegisterAdapter::set(0U);
}

void DivRegister::setBit(uint8_t pos, bool value)
{
  (void)pos;
  (void)value;
  set(0U);
}

auto DivRegister::testBitSystemTimer(uint8_t pos) const -> bool
{
  return (static_cast<uint16_t>(systemTimer_ >> pos) & 1U) != 0U;
}

void DivRegister::clock()
{
  ++systemTimer_;
  if ((systemTimer_ & SystemTimerDivMask) == 0U) {
    updateDiv();
  }
}

void DivRegister::updateDiv() { MemoryRegisterAdapter::set(MemoryRegisterAdapter::get() + 1U); }
