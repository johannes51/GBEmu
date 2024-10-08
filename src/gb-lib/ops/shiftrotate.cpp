#include "shiftrotate.h"

#include "location/location.h"

ops::OpResult ops::rr(Location& location, bool carry)
{
  const auto& value = location.getByte();
  const auto newCarry = (value & detail::LsbMask) > 0;
  uint8_t result = (value >> 1) | (static_cast<uint8_t>(carry) << (detail::BitSize - 1));
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

ops::OpResult ops::rrc(Location& location)
{
  const auto& value = location.getByte();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const uint8_t result = (value >> 1) | (value << (detail::BitSize - 1));
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

ops::OpResult ops::rl(Location& location, bool carry)
{
  const auto& value = location.getByte();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result = (value << 1) | static_cast<uint8_t>(carry);
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

ops::OpResult ops::rlc(Location& location)
{
  const auto& value = location.getByte();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result = (value << 1) | (value >> (detail::BitSize - 1));
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

ops::OpResult ops::sra(Location& location)
{
  const auto& value = location.getByte();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const auto oldMsb = value & detail::MsbMask;
  const uint8_t result = (value >> 1) | oldMsb;
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

ops::OpResult ops::sla(Location& location)
{
  const auto& value = location.getByte();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result = value << 1;
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

ops::OpResult ops::srl(Location& location)
{
  const auto& value = location.getByte();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const uint8_t result = value >> 1;
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

ops::OpResult ops::swap(Location& location)
{
  const uint8_t result = ((location.getByte() & 0x0F) << 4) | ((location.getByte() & 0xF0) >> 4);
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}
