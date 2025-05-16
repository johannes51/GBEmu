#include "gtest/gtest.h"

#include "mem/registers/registerbuffer.h"

class RegisterBufferTest : public ::testing::Test {
public:
  RegisterBufferTest()
      : a(0x0U)
  {
  }

protected:
  RegisterBuffer a;
};

TEST(RegisterBufferTestNF, Construction) { EXPECT_NO_THROW((RegisterBuffer { 0x00U })); }

TEST_F(RegisterBufferTest, Construction)
{
  a.setByte(0b01010101U);

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

TEST_F(RegisterBufferTest, SetGet)
{
  a.setByte(0b01010101U);

  EXPECT_EQ(0b01010101U, a.getByte());
  EXPECT_TRUE(a.testBit(0U));

  EXPECT_NO_THROW(a.setByte(0b10101010U));

  EXPECT_EQ(0b10101010U, a.getByte());
  EXPECT_FALSE(a.testBit(0U));
}

TEST_F(RegisterBufferTest, SetBit)
{
  a.setByte(0b10U);

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
