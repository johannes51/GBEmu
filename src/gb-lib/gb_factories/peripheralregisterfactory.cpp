#include "peripheralregisterfactory.h"

const std::unordered_map<PeripheralRegisters, address_type> PeripheralRegisterFactory::PeripheralRegisterAddresses = {
  { PeripheralRegisters::JOYP, 0xFF00 }, // NOLINT
  { PeripheralRegisters::SB, 0xFF01 }, // NOLINT
  { PeripheralRegisters::SC, 0xFF02 }, // NOLINT
  // { PeripheralRegisters::DIV, 0xFF04 }, // NOTE: Is it's own thing now
  { PeripheralRegisters::TIMA, 0xFF05 }, // NOLINT
  { PeripheralRegisters::TMA, 0xFF06 }, // NOLINT
  { PeripheralRegisters::TAC, 0xFF07 }, // NOLINT
  { PeripheralRegisters::IF, 0xFF0F }, // NOLINT
};

auto PeripheralRegisterFactory::getDiv() -> DivRegisterSP { return div_; }

auto PeripheralRegisterFactory::releaseDivApu() -> IRegisterAdapterUP { return std::move(div_apu_); }
