#include "opcodeview.h"

OpcodeView::OpcodeView(uint8_t value)
    : value_(value)
{
}

const uint8_t& OpcodeView::value() const { return value_; }

uint8_t OpcodeView::upperNibble() const { return value_ >> NIBBLE; }

uint8_t OpcodeView::lowerNibble() const { return value_ & LOWER_MASK; }
