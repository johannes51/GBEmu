#include "ppuregisterfactory.h"

const std::unordered_map<PpuRegisters, address_type> PpuRegisterFactory::PpuRegisterAddresses = {
  { PpuRegisters::LCDC, 0xFF40 }, // NOLINT
  { PpuRegisters::STAT, 0xFF41 }, // NOLINT
  { PpuRegisters::SCY, 0xFF42 }, // NOLINT
  { PpuRegisters::SCX, 0xFF43 }, // NOLINT
  { PpuRegisters::LY, 0xFF44 }, // NOLINT
  { PpuRegisters::LYC, 0xFF45 }, // NOLINT
  { PpuRegisters::DMA, 0xFF46 }, // NOLINT
  { PpuRegisters::BGP, 0xFF47 }, // NOLINT
  { PpuRegisters::OBP0, 0xFF48 }, // NOLINT
  { PpuRegisters::OBP1, 0xFF49 }, // NOLINT
  { PpuRegisters::WY, 0xFF4A }, // NOLINT
  { PpuRegisters::WX, 0xFF4B }, // NOLINT
};
