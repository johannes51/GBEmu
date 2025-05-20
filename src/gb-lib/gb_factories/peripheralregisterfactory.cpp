#include "peripheralregisterfactory.h"

const RegisterFactory<PeripheralRegisters>::InputMap PeripheralRegisterFactory::PeripheralRegisterAddresses = {
  { PeripheralRegisters::JOYP, { 0xFF00U, 0xCFU } }, // NOLINT
  { PeripheralRegisters::SB, { 0xFF01U, 0x00U } }, // NOLINT
  { PeripheralRegisters::SC, { 0xFF02U, 0x7EU } }, // NOLINT
  // { PeripheralRegisters::DIV, {0xFF04U} }, // NOTE: Is it's own thing now
  { PeripheralRegisters::TIMA, { 0xFF05U, 0x00U } }, // NOLINT
  { PeripheralRegisters::TMA, { 0xFF06U, 0x00U } }, // NOLINT
  { PeripheralRegisters::TAC, { 0xFF07U, 0xF8U } }, // NOLINT
  { PeripheralRegisters::IF, { 0xFF0FU, 0xE1U } }, // NOLINT
  { PeripheralRegisters::DMA, { 0xFF46U, 0x00U } }, // NOLINT
};

auto PeripheralRegisterFactory::getDiv() -> DivRegisterSP { return div_; }

auto PeripheralRegisterFactory::releaseDivApu() -> IRegisterAdapterUP { return std::move(div_apu_); }
