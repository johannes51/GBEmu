#include "gtest/gtest.h"

#include "mem/registers/memoryregisteradapter.h"

#include <memory>

#include "mock/mockbytelocationadapter.h"
#include "mock/testbank.h"

#include "mem/location8.h"

class MemoryRegisterAdapterTest : public ::testing::Test {
public:
  MemoryRegisterAdapterTest()
      : b(MockByteLocationAdapter::make(0U))
      , bRef(*b)
      , a(std::move(b))
  {
  }

protected:
  ByteLocationAdapterUP b;
  ByteLocationAdapter& bRef;
  MemoryRegisterAdapter a;
};

TEST(MemoryRegisterAdapterTestNF, Construction)
{
  ByteLocationAdapterUP b = nullptr;
  EXPECT_NO_THROW((MemoryRegisterAdapter { std::move(b) }));
}

TEST_F(MemoryRegisterAdapterTest, Construction)
{
  bRef.set(0b01010101U);

  EXPECT_EQ(0b01010101U, a.getByte());
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
  bRef.set(0b01010101U);

  EXPECT_EQ(0b01010101U, a.getByte());
  EXPECT_TRUE(a.testBit(0U));

  EXPECT_NO_THROW(a.setByte(0b10101010U));

  EXPECT_EQ(0b10101010U, a.getByte());
  EXPECT_FALSE(a.testBit(0U));
}

TEST_F(MemoryRegisterAdapterTest, SetBit)
{
  bRef.set(0b10U);

  ASSERT_FALSE(a.testBit(0U));
  ASSERT_TRUE(a.testBit(1U));

  EXPECT_NO_THROW(a.setBit(0U, true));
  EXPECT_EQ(0b11U, a.getByte());
  EXPECT_NO_THROW(a.setBit(0U, true));
  EXPECT_EQ(0b11U, a.getByte());

  EXPECT_NO_THROW(a.setBit(1U, false));
  EXPECT_EQ(0b01U, a.getByte());
  EXPECT_NO_THROW(a.setBit(1U, false));
  EXPECT_EQ(0b01U, a.getByte());
}
