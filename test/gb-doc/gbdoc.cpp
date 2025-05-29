#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <memory>

using namespace std::literals;

#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"
#include "gb_factories/ppufactory.h"

#include "cpu/cpu.h"
#include "cpu/registers/cpuregisters.h"
#include "mem/rest/variablelocation.h"
#include "peripherals/gbinterrupthandler.h"
#include "peripherals/gbtimer.h"
#include "peripherals/joypad.h"
#include "peripherals/serial.h"
#include "ppu/ppu.h"
#include "ppu/gbrenderer.h"

static const std::vector<std::pair<std::string, size_t>> romList = {
  {{"01"s}, {1256633U}} /* PASS! */,
  {{"02"s}, {161057U}} /* PASS */,
  {{"03"s}, {1066160U}} /* PASS! */,
  {{"04"s}, {1260504U}} /* PASS! */,
  {{"05"s}, {1761126U}} /* PASS! */,
  {{"06"s}, {241011U}} /* PASS! */,
  {{"07"s}, {587415}} /* PASS */,
  {{"08"s}, {221630U}} /* PASS! */,
  {{"09"s}, {4418120U}} /* PASS! */,
  {{"10"s}, {6712461U}} /* PASS! */,
  {{"11"s}, {7427500U}} /* PASS! */,
};

void print(std::ostream& s, IMemoryView& m, RegistersInterface& r)
{
  const auto pc = hlp::indirect(r.get(WordRegister::PC));
  s << std::hex << std::uppercase << std::setfill('0');
  s << "A:" << std::setw(2) << (unsigned)r.get(ByteRegister::A).get() << std::setw(0)
    << " F:" << std::setw(2) << (unsigned)r.get(ByteRegister::F).get() << std::setw(0)
    << " B:" << std::setw(2) << (unsigned)r.get(ByteRegister::B).get() << std::setw(0)
    << " C:" << std::setw(2) << (unsigned)r.get(ByteRegister::C).get() << std::setw(0)
    << " D:" << std::setw(2) << (unsigned)r.get(ByteRegister::D).get() << std::setw(0)
    << " E:" << std::setw(2) << (unsigned)r.get(ByteRegister::E).get() << std::setw(0)
    << " H:" << std::setw(2) << (unsigned)r.get(ByteRegister::H).get() << std::setw(0)
    << " L:" << std::setw(2) << (unsigned)r.get(ByteRegister::L).get() << std::setw(0)
    << " SP:" << std::setw(4) << (unsigned)r.get(WordRegister::SP).get() << std::setw(0)
    << " PC:" << std::setw(4) << (unsigned)pc << std::setw(0) << " PCMEM:" << std::setw(2)
    << (unsigned)m.getLocation8(pc).get() << "," << std::setw(2)
    << (unsigned)m.getLocation8(pc + 1).get() << "," << std::setw(2)
    << (unsigned)m.getLocation8(pc + 2).get() << "," << std::setw(2)
    << (unsigned)m.getLocation8(pc + 3).get() << "\n";
}

bool runTest(const std::string& number, const size_t limit)
{
  auto outFile = "cpu" + number + ".txt";
  auto romFile = number + ".gb";
  auto ramFile = number + ".sav";
  std::ofstream fileStream(outFile);

  std::cout << "Executing " << romFile<< "\n";

  std::vector<uint8_t> buffer;
  IoRegister divApu;

  CartUP cart;
  IMemoryWordViewUP mem;
  IoBankUP ioBank;
  std::unique_ptr<Cpu> cpu;
  RegistersInterface* reg = nullptr;
  TickableUP tim;
  TickableUP joy;
  TickableUP serial;
  // TickableUP ppu;
  IMemoryViewUP vram;
  IMemoryViewUP oam;
  auto ly = variableLocation(uint8_t{0x90U});
  {
    gb::CartLoader cl{romFile, ramFile};
    buffer.resize(cl.calculateNeccessarySize() + gb::MemoryFactory::getSize());
    cart = cl.constructCart(buffer);

    auto ioBank = std::make_unique<IoBank>();
    ioBank->registerRegister(0xFF44U, &ly);
    auto& ioBankRef = *ioBank;
    auto mf = gb::MemoryFactory(cart->getBanks(), std::move(ioBank), std::span{buffer}.subspan(cl.calculateNeccessarySize(), gb::MemoryFactory::getSize()));

    mem = mf.releaseMemory();

    auto ih = std::make_unique<GbInterruptHandler>(ioBankRef, mem->getLocation8(0xFFFFU));

    tim = std::make_unique<GbTimer>(ioBankRef, divApu, *ih->getIf());
    joy = std::make_unique<Joypad>(ioBankRef, *ih->getIf());
    serial = std::make_unique<Serial>(ioBankRef, *ih->getIf());

    // PpuFactory pf{ioBankRef, *mem, *ih->getIf(), mf.releaseVram(), mf.releaseOam()};

    vram = mf.releaseVram();
    oam = mf.releaseOam();
    // ppu = pf.constructPpu();

    auto cr = std::make_unique<CpuRegisters>();
    reg = cr.get();

    cpu = std::make_unique<Cpu>(*mem, std::move(cr), InstructionSetBuilder::construct(), std::move(ih));
  }

  print(fileStream, *mem, *reg);

  for (size_t lineCount = 1U; lineCount < limit; ) {
    if (lineCount >= limit - 1U) {
      std::stringstream s;
      print(s, *mem, *reg);
      const auto state = s.str();
      std::cout << state;
    }
    try {
      if (cpu->clock()) {
        ++lineCount;
        print(fileStream, *mem, *reg);
      }
      tim->clock();
      joy->clock();
      serial->clock();
      // ppu->clock();
    } catch(...) {
      print(fileStream, *mem, *reg);
      return false;
    }
  }
  return true;
}

int main()
{
  for (const auto& test : romList) {
    runTest(test.first, test.second);
  }

  return 0;
}
