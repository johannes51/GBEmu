#ifndef REGISTER16_H
#define REGISTER16_H

#include "../wordlocationadapter.h"

#include <cstdint>

#include "defines.h"

class Register16 final : public WordLocationAdapter {
public:
  explicit Register16(uint16_t& buffer);
  ~Register16() override = default;
  DISABLE_COPY_AND_MOVE(Register16)

  const uint16_t& get() const override;
  void set(const uint16_t& value) override;

private:
  uint16_t& buffer_;
};

#endif // REGISTER16_H
