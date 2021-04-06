#ifndef VARIABLEBYTE_H
#define VARIABLEBYTE_H

#include "location/locationbyte.h"

template <typename> class Location;

class VariableByte final : public LocationByte {
public:
  VariableByte(const uint8_t& variable = 0);
  DISABLE_COPY_AND_MOVE(VariableByte)

  uint8_t get() const override;
  void set(const uint8_t& value) override;

private:
  uint8_t variable_;
};

Location<uint8_t> variableLocation(const uint8_t& value);
Location<uint16_t> variableLocation(const uint8_t& lowValue, const uint8_t& highValue);

#endif // VARIABLEBYTE_H
