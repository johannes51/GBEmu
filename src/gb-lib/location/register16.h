#ifndef REGISTER16_H
#define REGISTER16_H

#include "location16.h"

#include <cstdint>
#include <memory>

#include "defines.h"

class Register16 : public Location16 {
public:
  explicit Register16(uint16_t& buffer);
  DISABLE_COPY_AND_MOVE(Register16)

  uint16_t& getReference();

  uint16_t get() const override;

  Register16& operator=(const uint16_t& rhs) override;

private:
  uint16_t& buffer_;
};

using Register16UP = std::unique_ptr<Register16>;

#endif // REGISTER16_H
