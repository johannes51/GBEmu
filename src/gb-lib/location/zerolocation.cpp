#include "zerolocation.h"

uint8_t ZeroLocation8::zero_ = { 0U };

auto ZeroLocation8::get() const -> const uint8_t& { return zero_; }

auto ZeroLocation8::operator=(const uint8_t& rhs) -> ZeroLocation8&
{
  (void)rhs;
  return *this;
}

uint16_t ZeroLocation16::zero_ = { 0U };

auto ZeroLocation16::get() const -> uint16_t { return zero_; }

auto ZeroLocation16::operator=(const uint16_t& rhs) -> ZeroLocation16&
{
  (void)rhs;
  return *this;
}
