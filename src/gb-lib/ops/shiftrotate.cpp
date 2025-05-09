#include "shiftrotate.h"

#include "constants.h"
#include "location/location8.h"

auto ops::rr(Location8& location, bool carry) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const uint8_t result
      = static_cast<unsigned int>(value >> 1U) | (static_cast<unsigned int>(carry) << (detail::BitSize - 1U));
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::rrc(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const uint8_t result
      = static_cast<unsigned int>(value >> 1U) | static_cast<unsigned int>(value << (detail::BitSize - 1U));
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::rl(Location8& location, bool carry) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result = static_cast<unsigned int>(value << 1U) | static_cast<uint8_t>(carry);
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::rlc(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result
      = static_cast<unsigned int>(value << 1U) | static_cast<unsigned int>(value >> (detail::BitSize - 1U));
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::sra(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const auto oldMsb = static_cast<unsigned int>(value & detail::MsbMask);
  const uint8_t result = static_cast<unsigned int>(value >> 1U) | oldMsb;
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::sla(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result = value << 1U;
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::srl(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const uint8_t result = value >> 1U;
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::swap(Location8& location) -> ops::OpResult
{
  const uint8_t result = (static_cast<unsigned int>(location.get() & MASK_LOWER_HALF_BYTE) << HALF_BYTE_SHIFT)
      | (static_cast<unsigned int>(location.get() & MASK_UPPER_HALF_BYTE) >> HALF_BYTE_SHIFT);
  location = result;
  return { (result == 0) ? FlagResult::Set : FlagResult::Reset, FlagResult::Reset, FlagResult::Reset,
    FlagResult::Reset };
}
