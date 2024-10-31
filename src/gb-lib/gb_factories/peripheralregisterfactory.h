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
  IE,
};

class PeripheralRegisterFactory : public RegisterFactory<PeripheralRegisters> {
public:
  explicit PeripheralRegisterFactory(const IMemoryViewSP& mem)
      : RegisterFactory(mem, PeripheralRegisterAddresses)
      , div_(std::make_shared<DivRegister>(mem))
      , div_apu_(std::make_shared<RegisterBuffer>())
  {
  }

  DivRegisterSP getDiv();
  IRegisterAdapterSP getDivApu();

private:
  static const std::unordered_map<PeripheralRegisters, address_type> PeripheralRegisterAddresses;
  DivRegisterSP div_ = nullptr;
  IRegisterAdapterSP div_apu_ = nullptr;
};

#endif // PERIPHERALREGISTERFACTORY_H
