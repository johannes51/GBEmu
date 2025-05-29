#ifndef ONELOCATION_H
#define ONELOCATION_H

#include "../ilocation8.h"

#include "defines.h"

class OneLocation final : public ILocation8 {
public:
  OneLocation() = default;
  DISABLE_COPY_AND_MOVE(OneLocation)
  ~OneLocation() override = default;

  const uint8_t& get() const override;
  OneLocation& operator=(const uint8_t& rhs) override;

  static ILocation8& instance();

private:
  static uint8_t one_;
};

#endif // ONELOCATION_H
