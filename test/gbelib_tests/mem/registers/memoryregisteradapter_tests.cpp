#include "gtest/gtest.h"

#include "mock/testbank.h"
#include <memory>

#include "location/location.h"

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
  *b->getLocation(0x0U) = uint8_t { 0b01010101U };

  EXPECT_EQ(0b01010101U, a.get());
  EXPECT_EQ(1U, a.testBit(0U));
  EXPECT_EQ(0U, a.testBit(1U));
  EXPECT_EQ(1U, a.testBit(2U));
  EXPECT_EQ(0U, a.testBit(3U));
  EXPECT_EQ(1U, a.testBit(4U));
  EXPECT_EQ(0U, a.testBit(5U));
  EXPECT_EQ(1U, a.testBit(6U));
  EXPECT_EQ(0U, a.testBit(7U));
}
