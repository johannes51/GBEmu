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
  auto writeLocation = memory.getWord(writeAddress);
  writeLocation.set(value);
  EXPECT_EQ(value, memory.getWord(readAddress).get());
}

void testMemoryRoundtrip(IMemoryView& memory, address_type rwAddress, uint16_t value)
{
  testMemoryRoundtrip(memory, rwAddress, rwAddress, value);
}

void testMemoryRoundtrip(IMemoryView& memory, address_type writeAddress, address_type readAddress, uint8_t value)
{
  auto writeLocation = memory.getByte(writeAddress);
  writeLocation.set(value);
  EXPECT_EQ(value, memory.getByte(readAddress).get());
}

void testMemoryRoundtrip(IMemoryView& memory, address_type rwAddress, uint8_t value)
{
  testMemoryRoundtrip(memory, rwAddress, rwAddress, value);
}

void testMemoryThrows(IMemoryView& memory, address_type testAddress) { EXPECT_ANY_THROW(memory.getWord(testAddress)); }

TEST(GBMemoryFactoryTest, ROM0t1)
{
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
  auto mem = f.constructMemoryLayout();
  EXPECT_EQ(0x3C, mem->getByte(startROM0).get());
  EXPECT_EQ(0xC9, mem->getByte(startROM0 + 1).get());
  EXPECT_ANY_THROW(mem->getByte(startROM0).set(0x00));
}

TEST(GBMemoryFactoryTest, ROM0t2)
{

  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
  auto mem = f.constructMemoryLayout();
  EXPECT_EQ(0x00, mem->getByte(startPC).get());
  EXPECT_EQ(0xC3, mem->getByte(startPC + 1).get());
  EXPECT_EQ(0x37, mem->getByte(startPC + 2).get());
  EXPECT_EQ(0x06, mem->getByte(startPC + 3).get());
  EXPECT_ANY_THROW(mem->getByte(startPC).set(0x00));
}

TEST(GBMemoryFactoryTest, ROM0t3)
{
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
  auto mem = f.constructMemoryLayout();
  unsigned val = mem->getWord(endROM0 - 1).get();
  EXPECT_EQ(0x066E, val);
  EXPECT_ANY_THROW(mem->getByte(endROM0).set(0x00));
}

TEST(GBMemoryFactoryTest, ROM1t1)
{
  auto f = MemoryFactory(std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
  auto mem = f.constructMemoryLayout();
  EXPECT_EQ(0xC3, mem->getByte(startROM1).get());
  EXPECT_EQ(0x20, mem->getByte(startROM1 + 1).get());
  EXPECT_ANY_THROW(mem->getByte(startROM1).set(0x00));
}

TEST(GBMemoryFactoryTest, WRAM0t1)
{
  auto mem = MemoryFactory(nullptr);
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0, value8);
  auto value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0, value16);
}

TEST(GBMemoryFactoryTest, WRAM0t2)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, endWRAM0, value8);

  testMemoryThrows(*gbLayout, endWRAM0);
}

TEST(GBMemoryFactoryTest, WRAM0t3)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, (startWRAM0 + endWRAM0) / 2, value8);
  auto value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, (startWRAM0 + endWRAM0) / 2, value16);
}

TEST(GBMemoryFactoryTest, WRAM1t1)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM1, value8);
  auto value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM1, value16);
}

TEST(GBMemoryFactoryTest, WRAM1t2)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, endWRAM1, value8);

  testMemoryThrows(*gbLayout, endWRAM1);
}

TEST(GBMemoryFactoryTest, WRAM1t3)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, (startWRAM1 + endWRAM1) / 2, value8);
  auto value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, (startWRAM1 + endWRAM1) / 2, value16);
}

TEST(GBMemoryFactoryTest, ECHOt1)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0, startECHO, value8);
  value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startECHO, startWRAM0, value8);
  auto value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0, startECHO, value16);
  value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startECHO, startWRAM0, value16);
}

TEST(GBMemoryFactoryTest, ECHOt2)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM1, startECHO + startWRAM1 - startWRAM0, value8);
  value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startECHO + startWRAM1 - startWRAM0, startWRAM1, value8);
  auto value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM1, startECHO + startWRAM1 - startWRAM0, value16);
  value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startECHO + startWRAM1 - startWRAM0, startWRAM1, value16);
}

TEST(GBMemoryFactoryTest, ECHOt3)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0 + endECHO - startECHO, endECHO, value8);
  value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, endECHO, startWRAM0 + endECHO - startECHO, value8);

  testMemoryThrows(*gbLayout, endECHO);
}

TEST(GBMemoryFactoryTest, NOTUSEDt1)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();

  auto value = static_cast<uint16_t>(rand());
  auto writeLocation = gbLayout->getWord(startNOTUSED);
  writeLocation.set(value);

  EXPECT_EQ(0, gbLayout->getWord(startNOTUSED).get());
}

TEST(GBMemoryFactoryTest, NOTUSEDt2)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();

  EXPECT_ANY_THROW(gbLayout->getWord(endNOTUSED));
}

TEST(GBMemoryFactoryTest, HRAMt1)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startHRAM, value8);
  auto value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startHRAM, value16);
}

TEST(GBMemoryFactoryTest, HRAMt2)
{
  auto mem = MemoryFactory { nullptr };
  auto gbLayout = mem.constructMemoryLayout();
  auto value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, endHRAM, value8);

  testMemoryThrows(*gbLayout, endHRAM);
}
