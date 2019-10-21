#include "gtest/gtest.h"

#include "gb_factories/memoryfactory.h"
#include "gb_factories/cartloader.h"
#include "mem/imemoryview.h"
#include "location/location.h"


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

void testMemoryRoundtrip(IMemoryView& memory, address_type writeAdress, address_type readAdress, uint16_t value)
{
  auto writeLocation = memory.getWord(writeAdress);
  writeLocation->set(value);
  ASSERT_EQ(value, memory.getWord(readAdress)->get());
}

void testMemoryRoundtrip(IMemoryView& memory, address_type rwAdress, uint16_t value)
{
  testMemoryRoundtrip(memory, rwAdress, rwAdress, value);
}

void testMemoryRoundtrip(IMemoryView& memory, address_type writeAdress, address_type readAdress, uint8_t value)
{
  auto writeLocation = memory.getByte(writeAdress);
  writeLocation->set(value);
  ASSERT_EQ(value, memory.getByte(readAdress)->get());
}

void testMemoryRoundtrip(IMemoryView& memory, address_type rwAdress, uint8_t value)
{
  testMemoryRoundtrip(memory, rwAdress, rwAdress, value);
}

void testMemoryThrows(IMemoryView& memory, address_type testAdress)
{
  ASSERT_ANY_THROW(memory.getWord(testAdress));
}

TEST(GBMemoryFactoryTest, testROM0_1) {
  auto f = MemoryFactory(std::make_unique<CartLoader>(
                           std::ifstream{"Tetris.gb", std::ios_base::binary},
                           std::fstream{"Tetris.sav", std::ios_base::binary}
                           ));
  auto mem = f.constructMemoryLayout();
  ASSERT_EQ(0xC3, mem->getByte(startROM0)->get());
  ASSERT_EQ(0x0C, mem->getByte(startROM0 + 1)->get());
  ASSERT_ANY_THROW(mem->getByte(startROM0)->set(0x00));
}

TEST(GBMemoryFactoryTest, testROM0_2) {
  auto f = MemoryFactory(std::make_unique<CartLoader>(
                           std::ifstream{"Tetris.gb", std::ios_base::binary},
                           std::fstream{"Tetris.sav", std::ios_base::binary}
                           ));
  auto mem = f.constructMemoryLayout();
  ASSERT_EQ(0x00, mem->getByte(startPC)->get());
  ASSERT_EQ(0xC3, mem->getByte(startPC + 1)->get());
  ASSERT_EQ(0x50, mem->getByte(startPC + 2)->get());
  ASSERT_EQ(0x01, mem->getByte(startPC + 3)->get());
  ASSERT_ANY_THROW(mem->getByte(startPC)->set(0x00));
}

TEST(GBMemoryFactoryTest, testROM0_3) {
  auto f = MemoryFactory(std::make_unique<CartLoader>(
                           std::ifstream{"Tetris.gb", std::ios_base::binary},
                           std::fstream{"Tetris.sav", std::ios_base::binary}
                           ));
  auto mem = f.constructMemoryLayout();
  uint val = mem->getWord(endROM0 - 1)->get();
  ASSERT_EQ(0x2F2F, val);
  ASSERT_ANY_THROW(mem->getByte(endROM0)->set(0x00));
}

TEST(GBMemoryFactoryTest, testROM1_1) {
  auto f = MemoryFactory(std::make_unique<CartLoader>(
                           std::ifstream{"Tetris.gb", std::ios_base::binary},
                           std::fstream{"Tetris.sav", std::ios_base::binary}
                           ));
  auto mem = f.constructMemoryLayout();
  ASSERT_EQ(0x2F, mem->getByte(endROM0 + 1)->get());
  ASSERT_EQ(0x2F, mem->getByte(endROM0 + 2)->get());
  ASSERT_ANY_THROW(mem->getByte(endROM0 + 1)->set(0x00));
}

TEST(GBMemoryFactoryTest, testWRAM0_1) {
  auto mem = MemoryFactory(nullptr);
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0, value8);
  uint16_t value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0, value16);
}

TEST(GBMemoryFactoryTest, testWRAM0_2) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, endWRAM0, value8);

  testMemoryThrows(*gbLayout, endWRAM0);
}

TEST(GBMemoryFactoryTest, testWRAM0_3) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, (startWRAM0 + endWRAM0) / 2, value8);
  uint16_t value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, (startWRAM0 + endWRAM0) / 2, value16);
}

TEST(GBMemoryFactoryTest, testWRAM1_1) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM1, value8);
  uint16_t value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM1, value16);
}

TEST(GBMemoryFactoryTest, testWRAM1_2) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, endWRAM1, value8);

  testMemoryThrows(*gbLayout, endWRAM1);
}

TEST(GBMemoryFactoryTest, testWRAM1_3) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, (startWRAM1 + endWRAM1) / 2, value8);
  uint16_t value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, (startWRAM1 + endWRAM1) / 2, value16);
}

TEST(GBMemoryFactoryTest, testECHO_1) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0, startECHO, value8);
  value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startECHO, startWRAM0, value8);
  uint16_t value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0, startECHO, value16);
  value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startECHO, startWRAM0, value16);
}

TEST(GBMemoryFactoryTest, testECHO_2) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM1, startECHO + startWRAM1 - startWRAM0, value8);
  value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startECHO + startWRAM1 - startWRAM0, startWRAM1, value8);
  uint16_t value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM1, startECHO + startWRAM1 - startWRAM0, value16);
  value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startECHO + startWRAM1 - startWRAM0, startWRAM1, value16);
}

TEST(GBMemoryFactoryTest, testECHO_3) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startWRAM0 + endECHO - startECHO, endECHO, value8);
  value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, endECHO, startWRAM0 + endECHO - startECHO, value8);

  testMemoryThrows(*gbLayout, endECHO);
}

TEST(GBMemoryFactoryTest, testNOTUSED_1) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();

  uint16_t value = static_cast<uint16_t>(rand());
  auto writeLocation = gbLayout->getWord(startNOTUSED);
  writeLocation->set(value);

  ASSERT_EQ(0, gbLayout->getWord(startNOTUSED)->get());
}

TEST(GBMemoryFactoryTest, testNOTUSED_2) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();

  ASSERT_ANY_THROW(gbLayout->getWord(endNOTUSED));
}

TEST(GBMemoryFactoryTest, testHRAM_1) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, startHRAM, value8);
  uint16_t value16 = static_cast<uint16_t>(rand());
  testMemoryRoundtrip(*gbLayout, startHRAM, value16);
}

TEST(GBMemoryFactoryTest, testHRAM_2) {
  auto mem = MemoryFactory{nullptr};
  auto gbLayout = mem.constructMemoryLayout();
  uint8_t value8 = static_cast<uint8_t>(rand());
  testMemoryRoundtrip(*gbLayout, endHRAM, value8);

  testMemoryThrows(*gbLayout, endHRAM);
}

