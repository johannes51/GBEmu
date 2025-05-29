#include "divregister.h"

DivRegister::DivRegister()
    : IoRegister(0x0U)
{
}

auto DivRegister::operator=(const uint8_t& rhs) -> DivRegister&
{
  setByte(rhs);
  return *this;
}

void DivRegister::setByte(uint8_t value)
{
  (void)value;
  systemTimer_ = 0U;
  IoRegister::setByte(0U);
}

void DivRegister::setBit(uint8_t pos, bool value)
{
  (void)pos;
  (void)value;
  setByte(0U);
}

auto DivRegister::testBitSystemTimer(uint8_t pos) const -> bool
{
  return (static_cast<uint16_t>(systemTimer_ >> pos) & 1U) != 0U;
}

void DivRegister::clock()
{
  ++systemTimer_;
  if ((systemTimer_ & SystemTimerDivMask) == 0U) {
    ++value_;
  }
}
