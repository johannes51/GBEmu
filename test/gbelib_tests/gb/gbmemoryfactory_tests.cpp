#include "gtest/gtest.h"

#include "gb_factories/memoryfactory.h"

#include "mock/mockiobank.h"

#include "gb_factories/cartloader.h"
#include "mem/ilocation8.h"
#include "mem/imemoryview.h"

using namespace std;
using namespace gb;

address_type startROM0 = 0x0000U;
address_type endROM0 = 0x3FFFU;
address_type startROM1 = 0x4000U;
address_type endROM1 = 0x7FFFU;
address_type startWRAM0 = 0xC000U;
address_type endWRAM0 = 0xCFFFU;
address_type startWRAM1 = 0xD000U;
address_type endWRAM1 = 0xDFFFU;
address_type startECHO = 0xE000U;
address_type endECHO = 0xFDFFU;
address_type startNOTUSED = 0xFEA0U;
address_type endNOTUSED = 0xFEFFU;
address_type startHRAM = 0xFF80U;
address_type endHRAM = 0xFFFEU;
address_type startPC = 0x0100U;

class GbMemoryFactoryTest : public ::testing::Test {
public:
  GbMemoryFactoryTest()
      : mem()
      , v()
      , cart()
  {
    CartLoader cl { "cpu_instrs.gb", "cpu_instrs.sav" };
    v.resize(cl.calculateNeccessarySize() + MemoryFactory::getSize());
    cart = cl.constructCart(v);
    auto f = MemoryFactory(cart->getBanks(), MockIoBank::make(), v);
    mem = f.releaseMemory();
  }

protected:
  IMemoryViewUP mem;
  std::vector<uint8_t> v;
  CartUP cart;
};

void testMemoryRoundtrip(IMemoryView& memory, address_type writeAddress, address_type readAddress, uint8_t value)
{
  auto& writeLocation = memory.getLocation8(writeAddress);
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

TEST_F(GbMemoryFactoryTest, ROM0t1)
{
  EXPECT_EQ(0x3CU, mem->getLocation8(startROM0).get());
  EXPECT_EQ(0xC9U, mem->getLocation8(startROM0 + 1).get());
  EXPECT_NO_THROW(mem->getLocation8(startROM0) = uint8_t(0x00U));
  EXPECT_EQ(0x3CU, mem->getLocation8(startROM0).get());
}

TEST_F(GbMemoryFactoryTest, ROM0t2)
{
  EXPECT_EQ(0x00U, mem->getLocation8(startPC).get());
  EXPECT_EQ(0xC3U, mem->getLocation8(startPC + 1).get());
  EXPECT_EQ(0x37U, mem->getLocation8(startPC + 2).get());
  EXPECT_EQ(0x06U, mem->getLocation8(startPC + 3).get());
  EXPECT_NO_THROW(mem->getLocation8(startPC + 1) = uint8_t(0x00U));
  EXPECT_EQ(0xC3U, mem->getLocation8(startPC + 1).get());
}

TEST_F(GbMemoryFactoryTest, ROM1t1)
{
  EXPECT_EQ(0xC3U, mem->getLocation8(startROM1).get());
  EXPECT_EQ(0x20U, mem->getLocation8(startROM1 + 1).get());
  EXPECT_NO_THROW(mem->getLocation8(startROM0) = uint8_t(0x00U));
  EXPECT_EQ(0x3CU, mem->getLocation8(startROM0).get());
}

TEST_F(GbMemoryFactoryTest, WRAM0t1)
{
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startWRAM0, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startWRAM0, value16);
}

TEST_F(GbMemoryFactoryTest, WRAM0t3)
{
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, (startWRAM0 + endWRAM0) / 2, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, (startWRAM0 + endWRAM0) / 2, value16);
}

TEST_F(GbMemoryFactoryTest, WRAM1t1)
{
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startWRAM1, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startWRAM1, value16);
}

TEST_F(GbMemoryFactoryTest, WRAM1t3)
{
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, (startWRAM1 + endWRAM1) / 2, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, (startWRAM1 + endWRAM1) / 2, value16);
}

TEST_F(GbMemoryFactoryTest, ECHOt1)
{
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startWRAM0, startECHO, value8);
  value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startECHO, startWRAM0, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startWRAM0, startECHO, value16);
  value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startECHO, startWRAM0, value16);
}

TEST_F(GbMemoryFactoryTest, ECHOt2)
{
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startWRAM1, startECHO + startWRAM1 - startWRAM0, value8);
  value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startECHO + startWRAM1 - startWRAM0, startWRAM1, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startWRAM1, startECHO + startWRAM1 - startWRAM0, value16);
  value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startECHO + startWRAM1 - startWRAM0, startWRAM1, value16);
}

TEST_F(GbMemoryFactoryTest, HRAMt1)
{
  auto value8 = static_cast<uint8_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startHRAM, value8);
  auto value16 = static_cast<uint16_t>(rand()); // NOLINT(concurrency-mt-unsafe)
  testMemoryRoundtrip(*mem, startHRAM, value16);
}
