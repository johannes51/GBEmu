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
#include "peripherals/joypad.h"
#include "peripherals/oamdma.h"
#include "peripherals/serial.h"
#include "ppufactory.h"

GbFactory::GbFactory(const std::string& romFile, const std::string& ramFile)
    : buffer_()
{
  constructMemory(romFile, ramFile);
}

auto GbFactory::constructSystem() -> SystemManagerUP
{
  auto cpu = constructCpu();
  auto peri = constructPeripherals();
  return std::make_unique<SystemManager>(
      std::move(cpu), std::move(mem_), std::move(peri), peripheralRF_->getAll(), pixBuf_, std::move(buffer_));
}

void GbFactory::constructMemory(const std::string& romFile, const std::string& ramFile)
{
  auto mf = gb::MemoryFactory(std::make_unique<gb::CartLoader>(romFile, ramFile), buffer_);
  ioBank_ = mf.getIoBank();
  ieBank_ = mf.getIeBank();
  peripheralRF_ = std::make_unique<PeripheralRegisterFactory>(*ioBank_);
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
  auto divApu = peripheralRF_->releaseDivApu();
  auto& divApuRef = *divApu;
  auto a = ApuFactory(*ioBank_, *mem_, std::move(divApu));
  auto p = PpuFactory(*mem_, *ioBank_, peripheralRF_->get(PeripheralRegisters::IF));
  auto ppu = p.constructPpu();
  pixBuf_ = &ppu->getBuffer();
  return { a.constructApu(), std::move(ppu), constructTimer(divApuRef), constructJoypad(), constructSerial(),
    constructOamDma() };
}

auto GbFactory::constructTimer(IRegisterAdapter& divApu) -> TickableSP
{
  return { std::make_shared<GbTimer>(peripheralRF_->getDiv(), divApu, peripheralRF_->get(PeripheralRegisters::TIMA),
      peripheralRF_->get(PeripheralRegisters::TMA), peripheralRF_->get(PeripheralRegisters::TAC),
      peripheralRF_->get(PeripheralRegisters::IF)) };
}

auto GbFactory::constructJoypad() -> TickableSP
{
  return std::make_shared<Joypad>(
      peripheralRF_->get(PeripheralRegisters::JOYP), peripheralRF_->get(PeripheralRegisters::IF));
}

auto GbFactory::constructSerial() -> TickableSP
{
  return std::make_shared<Serial>(peripheralRF_->get(PeripheralRegisters::SB),
      peripheralRF_->get(PeripheralRegisters::SC), peripheralRF_->get(PeripheralRegisters::IF));
}

auto GbFactory::constructOamDma() -> TickableSP
{
  return std::make_shared<OamDma>(peripheralRF_->get(PeripheralRegisters::DMA), *mem_);
}
