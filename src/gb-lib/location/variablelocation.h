#ifndef VARIABLELOCATION_H
#define VARIABLELOCATION_H

#include "location/location.h"

template <typename T> class VariableLocation final : public Location {
public:
  VariableLocation(const T& variable = 0);
  DISABLE_COPY_AND_MOVE(VariableLocation)

  const uint8_t& getByte() const override;
  const uint16_t& getWord() const override;
  Location& operator=(const uint8_t& rhs) override;
  Location& operator=(const uint16_t& rhs) override;

private:
  uint16_t variable_;
};

template <typename T>
VariableLocation<T>::VariableLocation(const T& variable)
    : Location(sizeof(T) > 1U ? Type::Both : Type::Single)
    , variable_()
{
  *this = variable;
}

template <typename T> auto VariableLocation<T>::getByte() const -> const uint8_t&
{
  return *reinterpret_cast<const uint8_t*>(&variable_);
}

template <typename T> auto VariableLocation<T>::getWord() const -> const uint16_t&
{
  if (!isWord()) {
    throw std::logic_error("Read word on single location");
  }
  return variable_;
}

template <typename T> auto VariableLocation<T>::operator=(const uint8_t& rhs) -> Location&
{
  variable_ = static_cast<uint16_t>(rhs);
  return *this;
}

template <typename T> auto VariableLocation<T>::operator=(const uint16_t& rhs) -> Location&
{
  if (!isWord()) {
    throw std::logic_error("Read word on single location");
  }
  variable_ = rhs;
  return *this;
}

LocationUP variableLocation(const uint8_t& value);
LocationUP variableLocation(const uint8_t& lowValue, const uint8_t& highValue);
LocationUP variableLocation(const uint16_t& value);

#endif // VARIABLELOCATION_H
