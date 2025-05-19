#include "apuregisterfactory.h"

const RegisterFactory<ApuRegisters>::InputMap ApuRegisterFactory::ApuRegisterAddresses = {
  { ApuRegisters::NR10, { 0xFF10U, 0x80U } }, // NOLINT
  { ApuRegisters::NR11, { 0xFF11U, 0xBFU } }, // NOLINT
  { ApuRegisters::NR12, { 0xFF12U, 0xF3U } }, // NOLINT
  { ApuRegisters::NR13, { 0xFF13U, 0xC1U } }, // NOLINT
  { ApuRegisters::NR14, { 0xFF14U, 0xBFU } }, // NOLINT
  { ApuRegisters::NR21, { 0xFF16U, 0x00U } }, // NOLINT
  { ApuRegisters::NR22, { 0xFF17U, 0x00U } }, // NOLINT
  { ApuRegisters::NR23, { 0xFF18U, 0x00U } }, // NOLINT
  { ApuRegisters::NR24, { 0xFF19U, 0xB8U } }, // NOLINT
  { ApuRegisters::NR30, { 0xFF1AU, 0x7FU } }, // NOLINT
  { ApuRegisters::NR31, { 0xFF1BU, 0x00U } }, // NOLINT
  { ApuRegisters::NR32, { 0xFF1CU, 0x9FU } }, // NOLINT
  { ApuRegisters::NR33, { 0xFF1DU, 0x00U } }, // NOLINT
  { ApuRegisters::NR34, { 0xFF1EU, 0xB8U } }, // NOLINT
  { ApuRegisters::NR41, { 0xFF20U, 0xC0U } }, // NOLINT
  { ApuRegisters::NR42, { 0xFF21U, 0x00U } }, // NOLINT
  { ApuRegisters::NR43, { 0xFF22U, 0x00U } }, // NOLINT
  { ApuRegisters::NR44, { 0xFF23U, 0xBFU } }, // NOLINT
  { ApuRegisters::NR50, { 0xFF24U, 0x77U } }, // NOLINT
  { ApuRegisters::NR51, { 0xFF25U, 0xF3U } }, // NOLINT
  { ApuRegisters::NR52, { 0xFF26U, 0xF1U } }, // NOLINT
};
