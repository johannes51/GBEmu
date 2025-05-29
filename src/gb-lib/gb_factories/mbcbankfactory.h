#ifndef MBCBANKFACTORY_H
#define MBCBANKFACTORY_H

#include <memory>
#include <vector>

#include "mem/rom/rombank.h"

class MbcBankFactory {
public:
  MbcBankFactory() = default;

  static IMemoryViewUP constructMbcBank(
      const uint8_t cartridgeType, RomBankUP rom0, std::vector<RomBankUP>&& rom1Banks, IMemoryViewUP ram0);
};

#endif // MBCBANKFACTORY_H
