#include "register16.h"

#include "constants.h"

Register16::Register16(uint16_t& buffer)
    : buffer_(buffer)
{
}

auto Register16::get() const -> const uint16_t& { return buffer_; }

void Register16::set(const uint16_t& value) { buffer_ = value; }
