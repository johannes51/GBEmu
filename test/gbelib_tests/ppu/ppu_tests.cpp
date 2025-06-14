#include "gtest/gtest.h"

#include "mock/mockregisteradapter.h"
#include "mock/mockrenderer.h"

#include "ppu/ppu.h"

TEST(PpuTest, Construction)
{
  std::unordered_map<PpuRegisters, IRegisterAdapterUP> registers;
  registers.insert({ PpuRegisters::LCDC, MockRegisterAdapter::make() });
  registers.insert({ PpuRegisters::STAT, MockRegisterAdapter::make() });
  registers.insert({ PpuRegisters::LY, MockRegisterAdapter::make() });
  registers.insert({ PpuRegisters::LYC, MockRegisterAdapter::make() });

  EXPECT_NO_THROW(Ppu p(nullptr, std::move(registers), *MockRegisterAdapter::make()));
}

TEST(PpuTest, Clock)
{
  constexpr auto area = MemoryArea { .from = 0x0000U, .to = 0xFFFFU };
  std::array<uint8_t, area.size()> b {};
  IoBank io { area, std::span(b.data(), area.size()) };
  auto ie = MockRegisterAdapter::make();
  PpuRegisterFactory pf { io };
  Ppu p(std::make_shared<MockRenderer>(), pf.getAll(), *ie);
  EXPECT_NO_THROW(p.clock());
}
