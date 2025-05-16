#include "gbfactory.h"

#include "apufactory.h"
#include "cartloader.h"
#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "instructionsetbuilder.h"
#include "mem/registers/singleregisterbank.h"
#include "memoryfactory.h"
#include "peripherals/gbinterrupthandler.h"
#include "peripherals/gbtimer.h"
#include "ppufactory.h"

GbFactory::GbFactory(const std::string& romFile, const std::string& ramFile)
    : cartLoader_(std::make_unique<gb::CartLoader>(romFile, ramFile))
    , buffer_()
{
  constructMemory();
}

auto GbFactory::constructSystem() -> SystemManagerUP
{
  auto cpu = constructCpu();
  auto peri = constructPeripherals();
  return std::make_unique<SystemManager>(
      std::move(cpu), std::move(mem_), std::move(peri), peripheralRF_->getAll(), pixBuf_);
}

void GbFactory::constructMemory()
{
  auto mf = gb::MemoryFactory(std::move(cartLoader_), buffer_);
  ioBank_ = mf.getIoBank();
  ieBank_ = mf.getIeBank();
  peripheralRF_ = std::make_unique<PeripheralRegisterFactory>(*mf.getIoBank());
  mem_ = mf.releaseMemory();
}

auto GbFactory::constructCpu() -> CpuUP
{
  auto ieRegister = ieBank_->asRegister();
  auto interruptHandler
      = std::make_unique<GbInterruptHandler>(peripheralRF_->get(PeripheralRegisters::IF), *ieRegister);
  return { std::make_unique<Cpu>(*mem_, std::make_unique<CpuRegisters>(), std::move(ieRegister),
      InstructionSetBuilder::construct(), std::move(interruptHandler)) };
}

auto GbFactory::constructPeripherals() -> std::vector<TickableSP>
{
  auto a = ApuFactory(*ioBank_, *mem_, peripheralRF_->releaseDivApu());
  auto p = PpuFactory(*mem_, *ioBank_, peripheralRF_->get(PeripheralRegisters::IF));
  auto ppu = p.constructPpu();
  pixBuf_ = &ppu->getBuffer();
  return { a.constructApu(), std::move(ppu), constructTimer() };
}

auto GbFactory::constructTimer() -> TickableSP
{
  return { std::make_shared<GbTimer>(peripheralRF_->getDiv(), *peripheralRF_->releaseDivApu(),
      peripheralRF_->get(PeripheralRegisters::TIMA), peripheralRF_->get(PeripheralRegisters::TMA),
      peripheralRF_->get(PeripheralRegisters::TAC), peripheralRF_->get(PeripheralRegisters::IF)) };
}
