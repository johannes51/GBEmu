#include "gtest/gtest.h"

#include "util/helpers.h"

#include "location/zerolocation.h"

TEST(HelperTest, Indirect) { EXPECT_EQ(address_type(0x0U), hlp::indirect(*std::make_unique<ZeroLocation>())); }

TEST(HelperTest, IndirectZeroPage)
{
  EXPECT_EQ(address_type(0xFF00U), hlp::indirectZeroPage(*std::make_unique<ZeroLocation>()));
}

TEST(HelperTest, Bits)
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
}
