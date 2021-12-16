#include "apuregisterfactory.h"

#include "mem/registers/memoryregisteradapter.h"

std::unordered_map<ApuRegisters, address_type> ApuRegisterFactory::ApuRegisterAdresses = {
  { { ApuRegisters::NR10 }, { 0xFF10 } },
  { { ApuRegisters::NR11 }, { 0xFF11 } },
  { { ApuRegisters::NR12 }, { 0xFF12 } },
  { { ApuRegisters::NR13 }, { 0xFF13 } },
  { { ApuRegisters::NR14 }, { 0xFF14 } },
  { { ApuRegisters::NR21 }, { 0xFF16 } },
  { { ApuRegisters::NR22 }, { 0xFF17 } },
  { { ApuRegisters::NR23 }, { 0xFF18 } },
  { { ApuRegisters::NR24 }, { 0xFF19 } },
  { { ApuRegisters::NR30 }, { 0xFF1A } },
  { { ApuRegisters::NR31 }, { 0xFF1B } },
  { { ApuRegisters::NR32 }, { 0xFF1C } },
  { { ApuRegisters::NR33 }, { 0xFF1D } },
  { { ApuRegisters::NR34 }, { 0xFF1E } },
  { { ApuRegisters::NR41 }, { 0xFF20 } },
  { { ApuRegisters::NR42 }, { 0xFF21 } },
  { { ApuRegisters::NR43 }, { 0xFF22 } },
  { { ApuRegisters::NR44 }, { 0xFF23 } },
  { { ApuRegisters::NR50 }, { 0xFF24 } },
  { { ApuRegisters::NR51 }, { 0xFF25 } },
  { { ApuRegisters::NR52 }, { 0xFF26 } },
};

ApuRegisterFactory::ApuRegisterFactory(const IMemoryViewSP& ioBank)
{
  for (const auto& regAddPair : ApuRegisterAdresses) {
    add(regAddPair.first, std::make_shared<MemoryRegisterAdapter>(ioBank, regAddPair.second));
  }
}
