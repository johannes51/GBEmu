#ifndef REGISTER8_H
#define REGISTER8_H

#include "../bytelocationadapter.h"

#include <cstdint>

#include "defines.h"

class Register8 : public ByteLocationAdapter {
public:
  explicit Register8(uint16_t& buffer, bool upper = true);
  ~Register8() override = default;
  DISABLE_COPY_AND_MOVE(Register8)

  const uint8_t& get() const override;
  void set(const uint8_t&) override;

private:
  uint16_t& buffer_;
  bool upper_;
};

#endif // REGISTER8_H
