#ifndef REGISTER_H
#define REGISTER_H

#include "location.h"

#include <cstdint>

#include "defines.h"

class Register : public Location {
public:
  explicit Register(uint16_t& buffer, bool upper = true);
  DISABLE_COPY_AND_MOVE(Register)

  uint8_t& getReference();

  const uint8_t& getByte() const override;
  const uint16_t& getWord() const override;

  Register& operator=(const uint8_t& rhs) override;
  Register& operator=(const uint16_t& rhs) override;

private:
  uint16_t& buffer_;
  bool upper_;
};

using RegisterUP = std::unique_ptr<Register>;

#endif // REGISTER_H
