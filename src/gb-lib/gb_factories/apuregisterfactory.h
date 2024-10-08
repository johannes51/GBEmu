#ifndef APUREGISTERFACTORY_H
#define APUREGISTERFACTORY_H

#include "registerfactory.h"

enum class ApuRegisters {
  NR10,
  NR11,
  NR12,
  NR13,
  NR14,
  NR21,
  NR22,
  NR23,
  NR24,
  NR30,
  NR31,
  NR32,
  NR33,
  NR34,
  NR41,
  NR42,
  NR43,
  NR44,
  NR50,
  NR51,
  NR52
};

class ApuRegisterFactory : public RegisterFactory<ApuRegisters> {
public:
  explicit ApuRegisterFactory(const IMemoryViewSP& ioBank)
      : RegisterFactory(ioBank, ApuRegisterAddresses)
  {
  }

private:
  static const std::unordered_map<ApuRegisters, address_type> ApuRegisterAddresses;
};

#endif // APUREGISTERFACTORY_H
