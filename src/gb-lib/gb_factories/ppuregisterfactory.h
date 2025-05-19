#ifndef PPUREGISTERFACTORY_H
#define PPUREGISTERFACTORY_H

#include "registerfactory.h"

enum class PpuRegisters {
  LCDC,
  STAT,
  SCY,
  SCX,
  LY,
  LYC,
  DMA,
  BGP,
  OBP0,
  OBP1,
  WY,
  WX,
};

class PpuRegisterFactory : public RegisterFactory<PpuRegisters> {
public:
  explicit PpuRegisterFactory(IoBank& ioBank)
      : RegisterFactory(ioBank, PpuRegisterAddresses)
  {
  }

private:
  static const RegisterFactory<PpuRegisters>::InputMap PpuRegisterAddresses;
};

#endif // PPUREGISTERFACTORY_H
