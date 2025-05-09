#ifndef REGISTER8_H
#define REGISTER8_H

#include "location8.h"

#include <cstdint>
#include <memory>

#include "defines.h"

class Register8 : public Location8 {
public:
  explicit Register8(uint16_t& buffer, bool upper = true);
  DISABLE_COPY_AND_MOVE(Register8)

  uint8_t& getReference();

  const uint8_t& get() const override;

  Register8& operator=(const uint8_t& rhs) override;

private:
  uint16_t& buffer_;
  bool upper_;
};

using Register8UP = std::unique_ptr<Register8>;

#endif // REGISTER8_H
