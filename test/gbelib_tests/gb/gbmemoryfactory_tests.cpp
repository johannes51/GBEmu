#include "gtest/gtest.h"

#include "gb_factories/cartloader.h"
#include "gb_factories/memoryfactory.h"
#include "mem/imemoryview.h"
#include "mem/location8.h"

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
  auto writeLocation = memory.getLocation16(writeAddress);
  writeLocation = value;
  EXPECT_EQ(value, memory.getLocation16(readAddress).get());
}

void testMemoryRoundtrip(IMemoryView& memory, address_type rwAddress, uint16_t value)
{
  testMemoryRoundtrip(memory, rwAddress, rwAddress, value);
}

void testMemoryRoundtrip(IMemoryView& memory, address_type writeAddress, address_type readAddress, uint8_t value)
{
  auto writeLocation = memory.getLocation8(writeAddress);
  writeLocation = value;
  EXPECT_EQ(value, memory.getLocation8(readAddress).get());
}

void testMemoryRoundtrip(IMemoryView& memory, address_type rwAddress, uint8_t value)
{
  testMemoryRoundtrip(memory, rwAddress, rwAddress, value);
}

void testMemoryThrowsByte(IMemoryView& memory, address_type testAddress)
{
  EXPECT_ANY_THROW(memory.getLocation8(testAddress));
}

void testMemoryThrowsWord(IMemoryView& memory, address_type testAddress)
{
  EXPECT_ANY_THROW(memory.getLocation16(testAddress));
}

TEST(GBMemoryFactoryTest, ROM0t1)
{
  auto v = std::vector<uint8_t> {};
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.releaseMemory();
  EXPECT_EQ(0x3C, mem->getLocation8(startROM0).get());
  EXPECT_EQ(0xC9, mem->getLocation8(startROM0 + 1).get());
  EXPECT_ANY_THROW(mem->getLocation8(startROM0) = uint8_t(0x00));
}

TEST(GBMemoryFactoryTest, ROM0t2)
{
  auto v = std::vector<uint8_t> {};
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.releaseMemory();
  EXPECT_EQ(0x00, mem->getLocation8(startPC).get());
  EXPECT_EQ(0xC3, mem->getLocation8(startPC + 1).get());
  EXPECT_EQ(0x37, mem->getLocation8(startPC + 2).get());
  EXPECT_EQ(0x06, mem->getLocation8(startPC + 3).get());
  EXPECT_ANY_THROW(mem->getLocation8(startPC) = uint8_t(0x00));
}

TEST(GBMemoryFactoryTest, ROM0t3)
{
  auto v = std::vector<uint8_t> {};
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.releaseMemory();
  unsigned val = mem->getLocation16(endROM0 - 1).get();
  EXPECT_EQ(0x066E, val);
  EXPECT_ANY_THROW(mem->getLocation8(endROM0) = uint8_t(0x00));
}

TEST(GBMemoryFactoryTest, ROM1t1)
{
  auto v = std::vector<uint8_t> {};
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.releaseMemory();
  EXPECT_EQ(0xC3, mem->getLocation8(startROM1).get());
  EXPECT_EQ(0x20, mem->getLocation8(startROM1 + 1).get());
  EXPECT_ANY_THROW(mem->getLocation8(startROM1) = uint8_t(0x00));
}

TEST(GBMemoryFactoryTest, WRAM0t1)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM0, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM0, value16);
}

TEST(GBMemoryFactoryTest, WRAM0t2)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, endWRAM0, value8);

  testMemoryThrowsWord(*gbLayout, endWRAM0);
}

TEST(GBMemoryFactoryTest, WRAM0t3)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, (startWRAM0 + endWRAM0) / 2, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, (startWRAM0 + endWRAM0) / 2, value16);
}

TEST(GBMemoryFactoryTest, WRAM1t1)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM1, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM1, value16);
}

TEST(GBMemoryFactoryTest, WRAM1t2)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, endWRAM1, value8);

  testMemoryThrowsWord(*gbLayout, endWRAM1);
}

TEST(GBMemoryFactoryTest, WRAM1t3)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, (startWRAM1 + endWRAM1) / 2, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, (startWRAM1 + endWRAM1) / 2, value16);
}

TEST(GBMemoryFactoryTest, ECHOt1)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
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
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
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
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startWRAM0 + endECHO - startECHO, endECHO, value8);
  value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, endECHO, startWRAM0 + endECHO - startECHO, value8);

  testMemoryThrowsWord(*gbLayout, endECHO);
}

TEST(GBMemoryFactoryTest, NOTUSEDt1)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();

  auto value = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  auto writeLocation = gbLayout->getLocation8(startNOTUSED);
  writeLocation = value;

  EXPECT_EQ(0, gbLayout->getLocation8(startNOTUSED).get());
}

TEST(GBMemoryFactoryTest, NOTUSEDt2)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();

  EXPECT_ANY_THROW(gbLayout->getLocation16(endNOTUSED));
}

TEST(GBMemoryFactoryTest, HRAMt1)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startHRAM, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, startHRAM, value16);
}

TEST(GBMemoryFactoryTest, HRAMt2)
{
  auto v = std::vector<uint8_t> {};
  auto mem = MemoryFactory { std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v };
  auto gbLayout = mem.releaseMemory();
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*gbLayout, endHRAM, value8);

  testMemoryThrowsWord(*gbLayout, endHRAM);
}
