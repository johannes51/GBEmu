#include "peripheralregisterfactory.h"

const RegisterFactory<PeripheralRegisters>::InputMap PeripheralRegisterFactory::PeripheralRegisterAddresses = {
  { PeripheralRegisters::JOYP, { 0xFF00, 0xCFU } }, // NOLINT
  { PeripheralRegisters::SB, { 0xFF01, 0x00U } }, // NOLINT
  { PeripheralRegisters::SC, { 0xFF02, 0x7EU } }, // NOLINT
  // { PeripheralRegisters::DIV, {0xFF04} }, // NOTE: Is it's own thing now
  { PeripheralRegisters::TIMA, { 0xFF05, 0x00U } }, // NOLINT
  { PeripheralRegisters::TMA, { 0xFF06, 0x00U } }, // NOLINT
  { PeripheralRegisters::TAC, { 0xFF07, 0xF8U } }, // NOLINT
  { PeripheralRegisters::IF, { 0xFF0F, 0xE1U } }, // NOLINT
};

auto PeripheralRegisterFactory::getDiv() -> DivRegisterSP { return div_; }

auto PeripheralRegisterFactory::releaseDivApu() -> IRegisterAdapterUP { return std::move(div_apu_); }
