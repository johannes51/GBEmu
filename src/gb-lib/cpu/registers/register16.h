#ifndef REGISTER16_H
#define REGISTER16_H

#include "mem/ilocation16.h"

class Register16 final : public ILocation16 {
public:
  Register16(uint16_t& buffer);
  DISABLE_COPY_AND_MOVE(Register16)
  ~Register16() override = default;

  const uint16_t& get() const override;
  Register16& operator=(const uint16_t& rhs) override;

private:
  uint16_t& buffer_;
};

#endif // REGISTER16_H
