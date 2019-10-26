#ifndef VARIABLEBYTE_H
#define VARIABLEBYTE_H

#include "location/locationbyte.h"

class VariableByte final : public LocationByte {
public:
  VariableByte(uint8_t variable = 0);
  DISABLE_COPY_AND_MOVE(VariableByte)

  uint8_t get() const override;
  void set(const uint8_t& value) override;

private:
  uint8_t variable_;
};

#endif // VARIABLEBYTE_H
