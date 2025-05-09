#include "gtest/gtest.h"

#include "mock/testbank.h"
#include <memory>

#include "location/location8.h"

#include "mem/registers/memoryregisteradapter.h"

class MemoryRegisterAdapterTest : public ::testing::Test {
public:
  MemoryRegisterAdapterTest()
      : b(std::make_shared<TestBank>(MemoryArea { 0x0U, 0x1U }))
      , a(b, 0x0U)
  {
  }

protected:
  std::shared_ptr<TestBank> b;
  MemoryRegisterAdapter a;
};

TEST(MemoryRegisterAdapterTestNF, Construction) { EXPECT_NO_THROW((MemoryRegisterAdapter { nullptr, 0x00U })); }

TEST_F(MemoryRegisterAdapterTest, Construction)
{
  *b->getLocation8(0x0U) = uint8_t { 0b01010101U };

  EXPECT_EQ(0b01010101U, a.get());
  EXPECT_TRUE(a.testBit(0U));
  EXPECT_FALSE(a.testBit(1U));
  EXPECT_TRUE(a.testBit(2U));
  EXPECT_FALSE(a.testBit(3U));
  EXPECT_TRUE(a.testBit(4U));
  EXPECT_FALSE(a.testBit(5U));
  EXPECT_TRUE(a.testBit(6U));
  EXPECT_FALSE(a.testBit(7U));
}

TEST_F(MemoryRegisterAdapterTest, SetGet)
{
  *b->getLocation8(0x0U) = uint8_t { 0b01010101U };

  EXPECT_EQ(0b01010101U, a.get());
  EXPECT_TRUE(a.testBit(0U));

  EXPECT_NO_THROW(a.set(0b10101010U));

  EXPECT_EQ(0b10101010U, a.get());
  EXPECT_FALSE(a.testBit(0U));
}

TEST_F(MemoryRegisterAdapterTest, SetBit)
{
  *b->getLocation8(0x0U) = uint8_t { 0b10U };

  ASSERT_FALSE(a.testBit(0U));
  ASSERT_TRUE(a.testBit(1U));

  EXPECT_NO_THROW(a.setBit(0U, true));
  EXPECT_EQ(0b11U, a.get());
  EXPECT_NO_THROW(a.setBit(0U, true));
  EXPECT_EQ(0b11U, a.get());

  EXPECT_NO_THROW(a.setBit(1U, false));
  EXPECT_EQ(0b01U, a.get());
  EXPECT_NO_THROW(a.setBit(1U, false));
  EXPECT_EQ(0b01U, a.get());
}
