#include "gtest/gtest.h"

#include "gb_factories/cartloader.h"
#include "gb_factories/memoryfactory.h"
#include "location/location.h"
#include "mem/imemoryview.h"

using namespace std;
using namespace gb;

address_type startROM0 = 0x0000;
address_type endROM0 = 0x3FFF;
address_type startROM1 = 0x4000;
address_type endROM1 = 0x7FFF;
address_type startWRAM0 = 0xC000;
address_type endWRAM0 = 0xCFFF;
address_type startWRAM1 = 0xD000;
address_type endWRAM1 = 0xDFFF;
address_type startECHO = 0xE000;
address_type endECHO = 0xFDFF;
address_type startNOTUSED = 0xFEA0;
address_type endNOTUSED = 0xFEFF;
address_type startHRAM = 0xFF80;
address_type endHRAM = 0xFFFE;
address_type startPC = 0x0100;

void testMemoryRoundtrip(IMemoryView& memory, address_type writeAddress, address_type readAddress, uint16_t value)
{
  auto writeLocation = memory.getLocation(writeAddress);
  *writeLocation = value;
  EXPECT_EQ(value, memory.getLocation(readAddress)->getWord());
}

void testMemoryRoundtrip(IMemoryView& memory, address_type rwAddress, uint16_t value)
{
  testMemoryRoundtrip(memory, rwAddress, rwAddress, value);
}

void testMemoryRoundtrip(IMemoryView& memory, address_type writeAddress, address_type readAddress, uint8_t value)
{
  auto writeLocation = memory.getLocation(writeAddress);
  *writeLocation = value;
  EXPECT_EQ(value, memory.getLocation(readAddress)->getByte());
}

void testMemoryRoundtrip(IMemoryView& memory, address_type rwAddress, uint8_t value)
{
  testMemoryRoundtrip(memory, rwAddress, rwAddress, value);
}

void testMemoryThrowsByte(IMemoryView& memory, address_type testAddress)
{
  EXPECT_ANY_THROW(memory.getLocation(testAddress));
}

void testMemoryThrowsWord(IMemoryView& memory, address_type testAddress)
{
  EXPECT_ANY_THROW(memory.getLocation(testAddress, true));
}

TEST(GBMemoryFactoryTest, ROM0t1)
{
  auto v = std::vector<uint8_t>{};
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.constructMemoryLayout();
  EXPECT_EQ(0x3C, mem->getLocation(startROM0)->getByte());
  EXPECT_EQ(0xC9, mem->getLocation(startROM0 + 1)->getByte());
  EXPECT_ANY_THROW(*mem->getLocation(startROM0) = uint8_t(0x00));
}

TEST(GBMemoryFactoryTest, ROM0t2)
{
  auto v = std::vector<uint8_t>{};
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.constructMemoryLayout();
  EXPECT_EQ(0x00, mem->getLocation(startPC)->getByte());
  EXPECT_EQ(0xC3, mem->getLocation(startPC + 1)->getByte());
  EXPECT_EQ(0x37, mem->getLocation(startPC + 2)->getByte());
  EXPECT_EQ(0x06, mem->getLocation(startPC + 3)->getByte());
  EXPECT_ANY_THROW(*mem->getLocation(startPC) = uint8_t(0x00));
}

TEST(GBMemoryFactoryTest, ROM0t3)
{
  auto v = std::vector<uint8_t>{};
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.constructMemoryLayout();
  unsigned val = mem->getLocation(endROM0 - 1)->getWord();
  EXPECT_EQ(0x066E, val);
  EXPECT_ANY_THROW(*mem->getLocation(endROM0) = uint8_t(0x00));
}

TEST(GBMemoryFactoryTest, ROM1t1)
{
  auto v = std::vector<uint8_t>{};
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.constructMemoryLayout();
  EXPECT_EQ(0xC3, mem->getLocation(startROM1)->getByte());
  EXPECT_EQ(0x20, mem->getLocation(startROM1 + 1)->getByte());
  EXPECT_ANY_THROW(*mem->getLocation(startROM1) = uint8_t(0x00));
}

TEST(GBMemoryFactoryTest, WRAM0t1)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory(nullptr, v);
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM0, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM0, value16);
}

TEST(GBMemoryFactoryTest, WRAM0t2)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, endWRAM0, value8);

  testMemoryThrowsWord(*gbLayout, endWRAM0);
}

TEST(GBMemoryFactoryTest, WRAM0t3)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, (startWRAM0 + endWRAM0) / 2, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, (startWRAM0 + endWRAM0) / 2, value16);
}

TEST(GBMemoryFactoryTest, WRAM1t1)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM1, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM1, value16);
}

TEST(GBMemoryFactoryTest, WRAM1t2)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, endWRAM1, value8);

  testMemoryThrowsWord(*gbLayout, endWRAM1);
}

TEST(GBMemoryFactoryTest, WRAM1t3)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, (startWRAM1 + endWRAM1) / 2, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, (startWRAM1 + endWRAM1) / 2, value16);
}

TEST(GBMemoryFactoryTest, ECHOt1)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM0, startECHO, value8);
  value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startECHO, startWRAM0, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM0, startECHO, value16);
  value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startECHO, startWRAM0, value16);
}

TEST(GBMemoryFactoryTest, ECHOt2)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM1, startECHO + startWRAM1 - startWRAM0, value8);
  value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startECHO + startWRAM1 - startWRAM0, startWRAM1, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM1, startECHO + startWRAM1 - startWRAM0, value16);
  value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startECHO + startWRAM1 - startWRAM0, startWRAM1, value16);
}

TEST(GBMemoryFactoryTest, ECHOt3)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM0 + endECHO - startECHO, endECHO, value8);
  value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, endECHO, startWRAM0 + endECHO - startECHO, value8);

  testMemoryThrowsWord(*gbLayout, endECHO);
}

TEST(GBMemoryFactoryTest, NOTUSEDt1)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();

  auto value = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  auto writeLocation = gbLayout->getLocation(startNOTUSED);
  *writeLocation = value;

  EXPECT_EQ(0, gbLayout->getLocation(startNOTUSED)->getWord());
}

TEST(GBMemoryFactoryTest, NOTUSEDt2)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();

  EXPECT_ANY_THROW(gbLayout->getLocation(endNOTUSED, true));
}

TEST(GBMemoryFactoryTest, HRAMt1)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startHRAM, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startHRAM, value16);
}

TEST(GBMemoryFactoryTest, HRAMt2)
{
  auto v = std::vector<uint8_t>{};
  auto mem = MemoryFactory { nullptr, v };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, endHRAM, value8);

  testMemoryThrowsWord(*gbLayout, endHRAM);
}
