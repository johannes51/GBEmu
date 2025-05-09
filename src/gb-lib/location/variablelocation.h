#ifndef VARIABLELOCATION_H
#define VARIABLELOCATION_H

#include "location/location16.h"
#include "location/location8.h"

class VariableLocation final : public Location8 {
public:
  VariableLocation(const uint8_t& variable = 0);
  DISABLE_COPY_AND_MOVE(VariableLocation)

  const uint8_t& get() const override;
  VariableLocation& operator=(const uint8_t& rhs) override;

private:
  uint8_t variable_;
};

Location8UP variableLocation(const uint8_t& value);
Location16UP variableLocation(const uint8_t& lowValue, const uint8_t& highValue);
Location16UP variableLocation(const uint16_t& value);

#endif // VARIABLELOCATION_H
