#include "object.h"

#include "ppu/ppu_constants.h"

Object::Object(std::span<uint8_t, 4> buffer)
    : buffer_(buffer)
{
}

auto Object::getY() const -> uint8_t { return buffer_[0]; }

auto Object::getX() const -> uint8_t { return buffer_[1]; }

auto Object::getTileIndex() const -> uint8_t { return buffer_[2]; }

auto Object::hasLowPriority() const -> bool { return (buffer_[3] & (1U << PriorityBit)) > 0; }

auto Object::isFlippedX() const -> bool { return (buffer_[3] & (1U << FlipXBit)) > 0; }

auto Object::isFlippedY() const -> bool { return (buffer_[3] & (1U << FlipYBit)) > 0; }

auto Object::isSecondPalette() const -> bool { return (buffer_[3] & (1U << PalleteBit)) > 0; }
