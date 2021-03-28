#include "opcodeview.h"

OpcodeView::OpcodeView(uint8_t value)
    : value_(value)
{
}

auto OpcodeView::value() const -> const uint8_t& { return value_; }

auto OpcodeView::upperNibble() const -> uint8_t { return value_ >> NIBBLE; }

auto OpcodeView::lowerNibble() const -> uint8_t { return value_ & LOWER_MASK; }
