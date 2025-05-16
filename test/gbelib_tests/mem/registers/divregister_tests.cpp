#include "gtest/gtest.h"

#include "mock/mockiobank.h"
#include "mock/testbank.h"

#include "mem/registers/divregister.h"

class DivRegisterTest : public ::testing::Test {
public:
  DivRegisterTest()
      : b_({ std::addressof(buf_), 1 })
  {
  }

protected:
  uint8_t buf_ = 0U;
  MockIoBank b_;

  void SetUp() override { buf_ = 0x00U; }
};

TEST_F(DivRegisterTest, Construction) { EXPECT_NO_THROW(DivRegister { b_ }); }

TEST_F(DivRegisterTest, ClockSysTimer)
{
  DivRegister div { b_ };

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
  DivRegister div { b_ };

  ASSERT_FALSE(div.testBitSystemTimer(0U));
  div.clock();
  ASSERT_TRUE(div.testBitSystemTimer(0U));
  for (auto i = 0U; i < 62; ++i) {
    div.clock();
    EXPECT_EQ(0x0U, div.getByte()) << i;
    EXPECT_FALSE(div.testBitSystemTimer(6U)) << i;
  }
  div.clock();
  // EXPECT_EQ(0x1U, div.getByte());
  // EXPECT_TRUE(div.testBitSystemTimer(6U)); TODO: hochkomisch
}

TEST_F(DivRegisterTest, SetReset)
{
  DivRegister div { b_ };
  buf_ = 0x0FU;

  EXPECT_EQ(0x0FU, div.getByte());

  EXPECT_NO_THROW(div.setByte(0b10101010U));
  EXPECT_EQ(0x0U, div.getByte());

  buf_ = 0x0FU;

  EXPECT_EQ(0x0FU, div.getByte());

  EXPECT_NO_THROW(div.setBit(1U, true));
  EXPECT_EQ(0x0U, div.getByte());
}
