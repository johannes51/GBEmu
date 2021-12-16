#ifndef APUREGISTERFACTORY_H
#define APUREGISTERFACTORY_H

#include <cstdint>

#include "registerfactory.h"

enum class ApuRegisters : uint8_t {
  NR10 = 0,
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
  ApuRegisterFactory(const IMemoryViewSP& ioBank);

private:
  static const std::unordered_map<ApuRegisters, address_type> ApuRegisterAdresses;
};

#endif // APUREGISTERFACTORY_H
