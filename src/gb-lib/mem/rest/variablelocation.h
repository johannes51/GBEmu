#ifndef VARIABLELOCATION_H
#define VARIABLELOCATION_H

#include "../ilocation16.h"
#include "../ilocation8.h"

class VariableLocation8 final : public ILocation8 {
public:
  explicit VariableLocation8(const uint8_t& variable = 0);
  DEFAULT_COPY(VariableLocation8)
  VariableLocation8(VariableLocation8&& other) noexcept;
  ~VariableLocation8() override = default;

  const uint8_t& get() const override;
  VariableLocation8& operator=(const uint8_t& rhs) override;

private:
  uint8_t variable_;
};

class VariableLocation16 final : public ILocation16 {
public:
  explicit VariableLocation16(const uint16_t& variable = 0);
  DEFAULT_COPY(VariableLocation16)
  VariableLocation16(VariableLocation16&& other) noexcept;
  ~VariableLocation16() override = default;

  const uint16_t& get() const override;
  VariableLocation16& operator=(const uint16_t& rhs) override;

private:
  uint16_t variable_;
};

VariableLocation8 variableLocation(const uint8_t& value);
VariableLocation16 variableLocation(const uint8_t& lowValue, const uint8_t& highValue);
VariableLocation16 variableLocation(const uint16_t& value);

#endif // VARIABLELOCATION_H
