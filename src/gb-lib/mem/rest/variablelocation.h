#ifndef VARIABLELOCATION_H
#define VARIABLELOCATION_H

#include "../bytelocationadapter.h"
#include "../location16.h"
#include "../location8.h"

class VariableLocation final : public ByteLocationAdapter {
public:
  VariableLocation(const uint8_t& variable = 0);
  DISABLE_COPY_AND_MOVE(VariableLocation)

  const uint8_t& get() const override;
  void set(const uint8_t& value) override;

private:
  uint8_t variable_;
};

Location8 variableLocation(const uint8_t& value);
Location16 variableLocation(const uint8_t& lowValue, const uint8_t& highValue);
Location16 variableLocation(const uint16_t& value);

#endif // VARIABLELOCATION_H
