#ifndef PERIPHERALREGISTERFACTORY_H
#define PERIPHERALREGISTERFACTORY_H

#include "registerfactory.h"

#include "mem/registers/divregister.h"
#include "mem/registers/registerbuffer.h"

enum class PeripheralRegisters {
  JOYP,
  SB,
  SC,
  TIMA,
  TMA,
  TAC,
  IF,
};

class PeripheralRegisterFactory : public RegisterFactory<PeripheralRegisters> {
public:
  explicit PeripheralRegisterFactory(IoBank& ioBank)
      : RegisterFactory(ioBank, PeripheralRegisterAddresses)
      , div_(std::make_shared<DivRegister>(ioBank))
      , div_apu_(std::make_unique<RegisterBuffer>())
  {
  }

  DivRegisterSP getDiv();
  IRegisterAdapterUP releaseDivApu();

private:
  static const std::unordered_map<PeripheralRegisters, address_type> PeripheralRegisterAddresses;
  DivRegisterSP div_ = nullptr;
  IRegisterAdapterUP div_apu_ = nullptr;
};

#endif // PERIPHERALREGISTERFACTORY_H
