#include "gtest/gtest.h"

#include "util/helpers.h"

#include "mem/rest/zerolocation.h"

TEST(HelperTest, Indirect) { EXPECT_EQ(address_type(0x0U), hlp::indirect({ std::make_unique<ZeroWordLocation>() })); }

TEST(HelperTest, IndirectZeroPage)
{
  EXPECT_EQ(address_type(0xFF00U), hlp::indirectZeroPage({ std::make_unique<ZeroByteLocation>() }));
}

TEST(HelperTest, Bits8)
{
  auto v = uint8_t { 0b01010101U };

  EXPECT_FALSE(hlp::checkBit(v, 7U));
  hlp::setBit(v, 7U);
  EXPECT_EQ(0b11010101U, v);
  EXPECT_TRUE(hlp::checkBit(v, 7U));

  EXPECT_TRUE(hlp::checkBit(v, 0U));
  hlp::clearBit(v, 0U);
  EXPECT_EQ(0b11010100U, v);
  EXPECT_FALSE(hlp::checkBit(v, 0U));

  v = { 0b01010101U };
  EXPECT_FALSE(hlp::checkBit(v, 7U));
  hlp::writeBit(v, 7U, true);
  EXPECT_EQ(0b11010101U, v);
  EXPECT_TRUE(hlp::checkBit(v, 7U));

  EXPECT_TRUE(hlp::checkBit(v, 0U));
  hlp::writeBit(v, 0U, false);
  EXPECT_EQ(0b11010100U, v);
  EXPECT_FALSE(hlp::checkBit(v, 0U));
}

TEST(HelperTest, Bits16)
{
  auto v = uint16_t { 0b0101010101010101U };

  EXPECT_FALSE(hlp::checkBit(v, 7U));
  hlp::setBit(v, 7U);
  EXPECT_EQ(0b0101010111010101U, v);
  EXPECT_TRUE(hlp::checkBit(v, 7U));

  EXPECT_TRUE(hlp::checkBit(v, 8U));
  hlp::clearBit(v, 8U);
  EXPECT_EQ(0b0101010011010101U, v);
  EXPECT_FALSE(hlp::checkBit(v, 8U));

  v = { 0b0101010101010101U };
  EXPECT_FALSE(hlp::checkBit(v, 7U));
  hlp::writeBit(v, 7U, true);
  EXPECT_EQ(0b0101010111010101U, v);
  EXPECT_TRUE(hlp::checkBit(v, 7U));

  EXPECT_TRUE(hlp::checkBit(v, 8U));
  hlp::writeBit(v, 8U, false);
  EXPECT_EQ(0b0101010011010101U, v);
  EXPECT_FALSE(hlp::checkBit(v, 8U));
}

TEST(HelperTest, BitFields8)
{
  auto v = uint8_t { 0b01010101U };

  EXPECT_EQ(0b1U, hlp::getBits(v, 0U, 1U));
  EXPECT_EQ(0b1U, hlp::getBits(v, 6U, 1U));
  EXPECT_EQ(0b0U, hlp::getBits(v, 7U, 1U));

  EXPECT_NO_THROW(hlp::getBits(v, 7U, 3U));
  EXPECT_ANY_THROW(hlp::getBits(v, 0U, 10U));

  EXPECT_EQ(0b0101U, hlp::getBits(v, 0U, 4U));
  EXPECT_EQ(0b1010U, hlp::getBits(v, 1U, 4U));
  EXPECT_EQ(0b010U, hlp::getBits(v, 5U, 3U));
}

TEST(HelperTest, BitFields16)
{
  auto v = uint16_t { 0b0101010101010101U };

  EXPECT_EQ(0b1U, hlp::getBits(v, 0U, 1U));
  EXPECT_EQ(0b1U, hlp::getBits(v, 6U, 1U));
  EXPECT_EQ(0b0U, hlp::getBits(v, 7U, 1U));
  EXPECT_EQ(0b1U, hlp::getBits(v, 8U, 1U));
  EXPECT_EQ(0b1U, hlp::getBits(v, 14U, 1U));
  EXPECT_EQ(0b0U, hlp::getBits(v, 15U, 1U));

  EXPECT_NO_THROW(hlp::getBits(v, 15U, 3U));
  EXPECT_ANY_THROW(hlp::getBits(v, 0U, 18U));

  EXPECT_EQ(0b0101U, hlp::getBits(v, 0U, 4U));
  EXPECT_EQ(0b1010U, hlp::getBits(v, 1U, 4U));
  EXPECT_EQ(0b010U, hlp::getBits(v, 5U, 3U));
  EXPECT_EQ(0b0101U, hlp::getBits(v, 8U, 4U));
  EXPECT_EQ(0b1010U, hlp::getBits(v, 9U, 4U));
  EXPECT_EQ(0b010U, hlp::getBits(v, 13U, 3U));
}
