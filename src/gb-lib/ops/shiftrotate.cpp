#include "shiftrotate.h"

#include "constants.h"
#include "mem/location8.h"

auto ops::rr(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::LsbMask) > 0U;
  const uint8_t result = static_cast<unsigned>(value >> 1U) | static_cast<unsigned>(value << (detail::BitSize - 1U));
  location = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::rr(Location8& location, bool carry) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const uint8_t result = static_cast<unsigned>(value >> 1U) | (static_cast<unsigned>(carry) << (detail::BitSize - 1U));
  location = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::rl(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result = static_cast<unsigned>(value << 1U) | static_cast<unsigned>(value >> (detail::BitSize - 1U));
  location = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::rl(Location8& location, bool carry) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result = static_cast<unsigned>(value << 1U) | static_cast<uint8_t>(carry);
  location = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::sra(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const auto oldMsb = static_cast<unsigned>(value & detail::MsbMask);
  const uint8_t result = static_cast<unsigned>(value >> 1U) | oldMsb;
  location = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::sla(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::MsbMask) > 0;
  const uint8_t result = value << 1U;
  location = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::srl(Location8& location) -> ops::OpResult
{
  const auto& value = location.get();
  const auto newCarry = (value & detail::LsbMask) > 0;
  const uint8_t result = value >> 1U;
  location = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = newCarry ? FlagResult::Set : FlagResult::Reset };
}

auto ops::swap(Location8& location) -> ops::OpResult
{
  const uint8_t result = (static_cast<unsigned>(location.get() & LOWER_NIBBLE_MASK) << NIBBLE_SHIFT)
      | (static_cast<unsigned>(location.get() & UPPER_NIBBLE_MASK) >> NIBBLE_SHIFT);
  location = result;
  return { .z = (result == 0) ? FlagResult::Set : FlagResult::Reset,
    .n = FlagResult::Reset,
    .h = FlagResult::Reset,
    .c = FlagResult::Reset };
}
