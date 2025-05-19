#include "ppuregisterfactory.h"

const RegisterFactory<PpuRegisters>::InputMap PpuRegisterFactory::PpuRegisterAddresses = {
  { PpuRegisters::LCDC, { 0xFF40, 0x91U } }, // NOLINT
  { PpuRegisters::STAT, { 0xFF41, 0x85U } }, // NOLINT
  { PpuRegisters::SCY, { 0xFF42, 0x00U } }, // NOLINT
  { PpuRegisters::SCX, { 0xFF43, 0x00U } }, // NOLINT
  { PpuRegisters::LY, { 0xFF44, 0x00U } }, // NOLINT
  { PpuRegisters::LYC, { 0xFF45, 0x00U } }, // NOLINT
  { PpuRegisters::DMA, { 0xFF46, 0xFFU } }, // NOLINT
  { PpuRegisters::BGP, { 0xFF47, 0xFCU } }, // NOLINT
  { PpuRegisters::OBP0, { 0xFF48, 0xFFU } }, // NOLINT
  { PpuRegisters::OBP1, { 0xFF49, 0xFFU } }, // NOLINT
  { PpuRegisters::WY, { 0xFF4A, 0x00U } }, // NOLINT
  { PpuRegisters::WX, { 0xFF4B, 0x00U } }, // NOLINT
};
