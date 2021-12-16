#include "apuregisterfactory.h"

#include "mem/registers/memoryregisteradapter.h"

const std::unordered_map<ApuRegisters, address_type> ApuRegisterFactory::ApuRegisterAdresses = {
  { ApuRegisters::NR10, 0xFF10 }, // NOLINT
  { ApuRegisters::NR11, 0xFF11 }, // NOLINT
  { ApuRegisters::NR12, 0xFF12 }, // NOLINT
  { ApuRegisters::NR13, 0xFF13 }, // NOLINT
  { ApuRegisters::NR14, 0xFF14 }, // NOLINT
  { ApuRegisters::NR21, 0xFF16 }, // NOLINT
  { ApuRegisters::NR22, 0xFF17 }, // NOLINT
  { ApuRegisters::NR23, 0xFF18 }, // NOLINT
  { ApuRegisters::NR24, 0xFF19 }, // NOLINT
  { ApuRegisters::NR30, 0xFF1A }, // NOLINT
  { ApuRegisters::NR31, 0xFF1B }, // NOLINT
  { ApuRegisters::NR32, 0xFF1C }, // NOLINT
  { ApuRegisters::NR33, 0xFF1D }, // NOLINT
  { ApuRegisters::NR34, 0xFF1E }, // NOLINT
  { ApuRegisters::NR41, 0xFF20 }, // NOLINT
  { ApuRegisters::NR42, 0xFF21 }, // NOLINT
  { ApuRegisters::NR43, 0xFF22 }, // NOLINT
  { ApuRegisters::NR44, 0xFF23 }, // NOLINT
  { ApuRegisters::NR50, 0xFF24 }, // NOLINT
  { ApuRegisters::NR51, 0xFF25 }, // NOLINT
  { ApuRegisters::NR52, 0xFF26 }, // NOLINT
};

ApuRegisterFactory::ApuRegisterFactory(const IMemoryViewSP& ioBank)
{
  for (const auto& regAddPair : ApuRegisterAdresses) {
    add(regAddPair.first, std::make_shared<MemoryRegisterAdapter>(ioBank, regAddPair.second));
  }
}
