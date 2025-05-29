#include "iobank.h"

#include "mem/common/fusedlocation16.h"
#include "mem/rest/onelocation.h"

IoBank::IoBank()
    : SingleAreaView(Io)
{
}

auto IoBank::getLocation8(const address_type address) -> ILocation8&
{
  auto* selectedRegister = selectRegister(address);
  if (selectedRegister == nullptr) {
    return { OneLocation::instance() };
  } else {
    return *selectedRegister;
  }
}

void IoBank::registerRegister(const address_type add, ILocation8* reg)
{
  if (registeredRegisters_.contains(add)) {
    throw std::invalid_argument { "Address already registered: " + std::to_string(add) };
  }
  registeredRegisters_.emplace(add, reg);
}

auto IoBank::selectRegister(const address_type add) -> ILocation8*
{
  return registeredRegisters_.contains(add) ? registeredRegisters_[add] : nullptr;
}
