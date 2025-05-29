#ifndef REGISTER8_H
#define REGISTER8_H

#include "mem/ilocation8.h"

#include "defines.h"

class Register8 : public ILocation8 {
public:
  explicit Register8(uint16_t& buffer, bool upper);
  DISABLE_COPY_AND_MOVE(Register8)
  ~Register8() override = default;

  const uint8_t& get() const override;
  Register8& operator=(const uint8_t& rhs) override;

private:
  uint16_t& buffer_;
  bool upper_;
};

#endif // REGISTER8_H
