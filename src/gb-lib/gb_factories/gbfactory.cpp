#include "gbfactory.h"

#include "apu/apu.h"
#include "apufactory.h"
#include "cpu/cpu.h"
#include "cpu/registers/cpuregisters.h"
#include "instructionsetbuilder.h"
#include "mem/rest/singleregisterbank.h"
#include "memoryfactory.h"
#include "peripherals/gbinterrupthandler.h"
#include "peripherals/gbtimer.h"
#include "peripherals/joypad.h"
#include "peripherals/oamdma.h"
#include "peripherals/serial.h"
#include "ppufactory.h"

GbFactory::GbFactory(const std::string& romFile, const std::string& ramFile)
    : buffer_()
    , cart_(buildCart(romFile, ramFile))
    , ioBank_()
    , vram_()
    , oam_()
    , mem_(constructMemory())
{
}

auto GbFactory::constructSystem() -> SystemManagerUP
{
  auto cpu = constructCpu();
  auto peri = constructPeripherals();
  return std::make_unique<SystemManager>(
      std::move(cpu), std::move(mem_), std::move(cart_), std::move(peri), pixBuf_, std::move(buffer_));
}

auto GbFactory::buildCart(const std::string& romFile, const std::string& ramFile) -> CartUP
{
  auto loader = gb::CartLoader { romFile, ramFile };
  buffer_.resize(loader.calculateNeccessarySize() + gb::MemoryFactory::getSize());
  auto result = loader.constructCart(std::span { buffer_ });

  return result;
}

auto GbFactory::constructMemory() -> IMemoryWordViewUP
{
  auto ioBank = std::make_unique<IoBank>();
  ioBank_ = ioBank.get();
  auto remainingSpan
      = std::span { buffer_ }.subspan(buffer_.size() - gb::MemoryFactory::getSize(), gb::MemoryFactory::getSize());
  auto mf = gb::MemoryFactory(cart_->getBanks(), std::move(ioBank), remainingSpan);
  vram_ = mf.releaseVram();
  oam_ = mf.releaseOam();
  return mf.releaseMemory();
}

auto GbFactory::constructCpu() -> std::unique_ptr<Cpu>
{
  auto interruptHandler = std::make_unique<GbInterruptHandler>(*ioBank_, mem_->getLocation8(gb::MemoryFactory::IE));
  if_ = interruptHandler->getIf();
  return { std::make_unique<Cpu>(
      *mem_, std::make_unique<CpuRegisters>(), InstructionSetBuilder::construct(), std::move(interruptHandler)) };
}

auto GbFactory::constructPeripherals() -> std::vector<TickableUP>
{
  auto a = ApuFactory(*ioBank_, *mem_);
  auto apu = a.constructApu();

  auto t = constructTimer(apu->getDivApu());

  auto p = PpuFactory(*ioBank_, *mem_, *if_, std::move(vram_), std::move(oam_));
  auto ppu = p.constructPpu();
  pixBuf_ = &ppu->getBuffer();

  std::vector<TickableUP> result;
  result.push_back(std::move(apu));
  result.push_back(std::move(ppu));
  result.push_back(std::move(t));
  result.push_back(constructJoypad());
  result.push_back(constructSerial());
  result.push_back(constructOamDma());

  return result;
}

auto GbFactory::constructTimer(IRegisterAdapter& divApu) -> TickableUP
{
  return std::make_unique<GbTimer>(*ioBank_, divApu, *if_);
}

auto GbFactory::constructJoypad() -> TickableUP { return std::make_unique<Joypad>(*ioBank_, *if_); }

auto GbFactory::constructSerial() -> TickableUP { return std::make_unique<Serial>(*ioBank_, *if_); }

auto GbFactory::constructOamDma() -> TickableUP { return std::make_unique<OamDma>(*ioBank_, *mem_); }
