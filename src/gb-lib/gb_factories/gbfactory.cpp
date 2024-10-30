#include "gbfactory.h"

#include "apufactory.h"
#include "cartloader.h"
#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "instructionsetbuilder.h"
#include "memoryfactory.h"
#include "peripherals/gbinterrupthandler.h"
#include "ppufactory.h"

GbFactory::GbFactory(const std::string& romFile, const std::string& ramFile)
    : cartLoader_(std::make_unique<gb::CartLoader>(romFile, ramFile))
    , buffer_()
{
  constructMemory();
}

auto GbFactory::constructSystem() -> SystemManagerUP
{
  return std::make_unique<SystemManager>(constructCpu(), constructPeripherals(), pixBuf_);
}

void GbFactory::constructMemory()
{
  auto mf = gb::MemoryFactory(std::move(cartLoader_), buffer_);
  mem_ = mf.constructMemoryLayout();
  peripheralRF_ = std::make_unique<PeripheralRegisterFactory>(mem_);
}

auto GbFactory::constructCpu() -> CpuUP
{
  return std::make_unique<Cpu>(std::make_unique<CpuRegisters>(), mem_, InstructionSetBuilder::construct(),
      std::make_unique<GbInterruptHandler>(
          peripheralRF_->get(PeripheralRegisters::IF), peripheralRF_->get(PeripheralRegisters::IE)));
}

auto GbFactory::constructPeripherals() -> std::vector<TickableSP>
{
  auto a = ApuFactory(ioBank_);
  auto p = PpuFactory(mem_);
  auto ppu = p.constructPpu();
  pixBuf_ = &ppu->getBuffer();
  return { a.constructApu(), std::move(ppu) };
}
