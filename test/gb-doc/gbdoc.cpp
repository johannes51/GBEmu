#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std::literals;

#include "util/helpers.h"

#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"
#include "gb_factories/peripheralregisterfactory.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "mem/registers/singleregisterbank.h"
#include "peripherals/gbinterrupthandler.h"
#include "peripherals/gbtimer.h"

static const std::vector<std::pair<std::string, size_t>> romList = {
  {{"01"s}, {1256633U}} /* PASS! */,
  {{"02"s}, {152036U}} /* Interrupt handling 161057 */,
  {{"03"s}, {1066160U}} /* PASS! */,
  {{"04"s}, {1260504U}} /* PASS! */,
  {{"05"s}, {1761126U}} /* PASS! */,
  {{"06"s}, {241011U}} /* PASS! */,
  {{"07"s}, {254075U}} /* RET failt, PC zu hoch? 587415 */,
  {{"08"s}, {221630U}} /* PASS! */,
  {{"09"s}, {4418120U}} /* PASS! */,
  {{"10"s}, {6712461U}} /* PASS! */,
  {{"11"s}, {7427500U}} /* PASS! */,
};

static std::vector<uint8_t> buffer;

void print(std::ostream& s, IMemoryView& m, RegistersInterface& r)
{
  const auto pc = hlp::indirect(r.get(WordRegister::PC));
  s << std::hex << std::uppercase << std::setfill('0');
  s << "A:" << std::setw(2) << (unsigned int)r.get(ByteRegister::A).get() << std::setw(0)
    << " F:" << std::setw(2) << (unsigned int)r.get(ByteRegister::F).get() << std::setw(0)
    << " B:" << std::setw(2) << (unsigned int)r.get(ByteRegister::B).get() << std::setw(0)
    << " C:" << std::setw(2) << (unsigned int)r.get(ByteRegister::C).get() << std::setw(0)
    << " D:" << std::setw(2) << (unsigned int)r.get(ByteRegister::D).get() << std::setw(0)
    << " E:" << std::setw(2) << (unsigned int)r.get(ByteRegister::E).get() << std::setw(0)
    << " H:" << std::setw(2) << (unsigned int)r.get(ByteRegister::H).get() << std::setw(0)
    << " L:" << std::setw(2) << (unsigned int)r.get(ByteRegister::L).get() << std::setw(0)
    << " SP:" << std::setw(4) << (unsigned int)r.get(WordRegister::SP).get() << std::setw(0)
    << " PC:" << std::setw(4) << (unsigned int)pc << std::setw(0) << " PCMEM:" << std::setw(2)
    << (unsigned int)m.getLocation8(pc).get() << "," << std::setw(2)
    << (unsigned int)m.getLocation8(pc + 1).get() << "," << std::setw(2)
    << (unsigned int)m.getLocation8(pc + 2).get() << "," << std::setw(2)
    << (unsigned int)m.getLocation8(pc + 3).get() << std::endl;
}

bool runTest(const std::string& number, const size_t limit)
{
  auto outFile = "cpu" + number + ".txt";
  auto romFile = number + ".gb";
  auto ramFile = number + ".sav";
  std::ofstream fileStream(outFile);

  std::shared_ptr<Cpu> cpu;
  std::shared_ptr<GbTimer> t;
      CpuRegisters* r = nullptr;

  auto mf = gb::MemoryFactory(std::make_unique<gb::CartLoader>(romFile, ramFile), buffer);
  auto peripheralRF = PeripheralRegisterFactory(*mf.getIoBank());
  auto m = mf.releaseMemory();
  {
    auto r_up = std::make_unique<CpuRegisters>();
    r = r_up.get();

    t = std::make_shared<GbTimer>(peripheralRF.getDiv(), *peripheralRF.releaseDivApu(),
        peripheralRF.get(PeripheralRegisters::TIMA), peripheralRF.get(PeripheralRegisters::TMA),
        peripheralRF.get(PeripheralRegisters::TAC), peripheralRF.get(PeripheralRegisters::IF));
    auto ie = mf.getIeBank()->asRegister();
    auto ih = std::make_unique<GbInterruptHandler>(peripheralRF.get(PeripheralRegisters::IF), *ie);
    cpu = std::make_shared<Cpu>(*m, std::move(r_up), std::move(ie), InstructionSetBuilder::construct(), std::move(ih));
  }
  m->getLocation8(0xFF44U) = 0x90U;
  print(fileStream, *m, *r);

  for (size_t lineCount = 1U; lineCount < limit; ) {
    if (lineCount >= limit - 1U) {
      std::stringstream s;
      print(s, *m, *r);
      const auto state = s.str();
      std::cout << state;
    }
    try {
      if (cpu->clock()) {
        ++lineCount;
        print(fileStream, *m, *r);
      }
      t->clock();
    } catch(...) {
      print(fileStream, *m, *r);
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
