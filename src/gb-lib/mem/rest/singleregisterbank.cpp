#include "singleregisterbank.h"

#include <stdexcept>

#include "../common/fusedlocation16.h"

SingleRegisterBank::SingleRegisterBank(const address_type& start, const uint8_t& initial)
    : start_(start)
    , loc_(initial)
{
}

auto SingleRegisterBank::getLocation8(const address_type address) -> ILocation8&
{
  if (address != start_) {
    throw std::invalid_argument("Out of bounds");
  }
  return loc_;
}
