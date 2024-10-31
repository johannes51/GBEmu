#include "gtest/gtest.h"

#include "mock/testbank.h"

#include "mem/registers/divregister.h"

class DivRegisterTest : public ::testing::Test {
public:
  DivRegisterTest()
      : mem_(std::make_shared<TestBank>(MemoryArea { 0xFF00U, 0xFFFFU }))
  {
  }

protected:
  std::shared_ptr<TestBank> mem_;

  void SetUp() override { *mem_->getLocation(0xFF04U) = uint8_t { 0x00U }; }
};

TEST_F(DivRegisterTest, Construction) { EXPECT_NO_THROW(DivRegister { mem_ }); }

TEST_F(DivRegisterTest, ClockSysTimer)
{
  DivRegister div { mem_ };

  EXPECT_FALSE(div.testBitSystemTimer(0U));
  div.clock();
  EXPECT_TRUE(div.testBitSystemTimer(0U));

  div.clock();
  EXPECT_FALSE(div.testBitSystemTimer(0U));
  EXPECT_TRUE(div.testBitSystemTimer(1U));

  div.clock();
  EXPECT_TRUE(div.testBitSystemTimer(0U));
  EXPECT_TRUE(div.testBitSystemTimer(1U));
}

TEST_F(DivRegisterTest, CycleDivTimer)
{
  DivRegister div { mem_ };

  ASSERT_FALSE(div.testBitSystemTimer(0U));
  div.clock();
  ASSERT_TRUE(div.testBitSystemTimer(0U));
  for (auto i = 0U; i < 62; ++i) {
    div.clock();
    EXPECT_EQ(0x0U, div.get()) << i;
    EXPECT_FALSE(div.testBitSystemTimer(6U)) << i;
  }
  div.clock();
  EXPECT_EQ(0x1U, div.get());
  EXPECT_TRUE(div.testBitSystemTimer(6U));
}

TEST_F(DivRegisterTest, SetReset)
{
  DivRegister div { mem_ };
  *mem_->getLocation(0xFF04U) = uint8_t { 0x0FU };

  EXPECT_EQ(0x0FU, div.get());

  EXPECT_NO_THROW(div.set(0b10101010U));
  EXPECT_EQ(0x0U, div.get());

  *mem_->getLocation(0xFF04U) = uint8_t { 0x0FU };

  EXPECT_EQ(0x0FU, div.get());

  EXPECT_NO_THROW(div.setBit(1U, true));
  EXPECT_EQ(0x0U, div.get());
}
