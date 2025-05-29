#include "gtest/gtest.h"

#include "mock/mockiobank.h"
#include "mock/testbank.h"

#include "io/divregister.h"

class DivRegisterTest : public ::testing::Test {
public:
  DivRegisterTest()
      : b_()
  {
  }

protected:
  MockIoBank b_;

  void SetUp() override { }
};

TEST_F(DivRegisterTest, Construction) { EXPECT_NO_THROW(DivRegister {}); }

TEST_F(DivRegisterTest, ClockSysTimer)
{
  DivRegister div {};

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
  DivRegister div {};

  ASSERT_FALSE(div.testBitSystemTimer(0U));
  div.clock();
  ASSERT_TRUE(div.testBitSystemTimer(0U));
  for (auto i = 0U; i < 62; ++i) {
    div.clock();
    EXPECT_EQ(0x0U, div.getByte()) << i;
    EXPECT_FALSE(div.testBitSystemTimer(6U)) << i;
  }
  div.clock();
  EXPECT_EQ(0x1U, div.getByte());
  EXPECT_TRUE(div.testBitSystemTimer(6U));
}

TEST_F(DivRegisterTest, SetReset)
{
  DivRegister div {};

  for (auto i = 0U; i < 63U; ++i) {
    div.clock();
  }
  EXPECT_EQ(0x0U, div.getByte());
  div.clock();

  EXPECT_NE(0x0U, div.getByte());
  EXPECT_NO_THROW(div.setByte(0b10101010U));
  EXPECT_EQ(0x0U, div.getByte());

  for (auto i = 0U; i < 63U; ++i) {
    div.clock();
  }
  EXPECT_EQ(0x0U, div.getByte());
  div.clock();

  EXPECT_NE(0x0U, div.getByte());
  EXPECT_NO_THROW(div.setBit(1U, true));
  EXPECT_EQ(0x0U, div.getByte());
}
