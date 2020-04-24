#ifndef OPCODEVIEW_H
#define OPCODEVIEW_H

#include <stdint.h>

class OpcodeView {
public:
  explicit OpcodeView(uint8_t value);

  const uint8_t& value() const;
  uint8_t upperNibble() const;
  uint8_t lowerNibble() const;

private:
  static constexpr uint8_t NIBBLE = 4;
  static constexpr uint8_t LOWER_MASK = 0x0F;

  const uint8_t value_;
};

#endif // OPCODEVIEW_H
