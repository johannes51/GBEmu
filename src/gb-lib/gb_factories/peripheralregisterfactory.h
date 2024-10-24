#ifndef PERIPHERALREGISTERFACTORY_H
#define PERIPHERALREGISTERFACTORY_H

#include "registerfactory.h"

enum class PeripheralRegisters {
  JOYP,
  SB,
  SC,
  DIV,
  TIMA,
  TMA,
  TAC,
  IF,
  IE,
};

class PeripheralRegisterFactory : public RegisterFactory<PeripheralRegisters> {
public:
  explicit PeripheralRegisterFactory(const IMemoryViewSP& ioBank)
      : RegisterFactory(ioBank, PeripheralRegisterAddresses)
  {
  }

private:
  static const std::unordered_map<PeripheralRegisters, address_type> PeripheralRegisterAddresses;
};

#endif // PERIPHERALREGISTERFACTORY_H
