#include "gtest/gtest.h"

#include "ppu/pixelbuffer.h"

TEST(PixelbufferTest, Construction) { EXPECT_NO_THROW(GbPixelBuffer {}); }

TEST(PixelbufferTest, At)
{
  PixelBuffer<uint8_t, 10U, 10U> p {};
  const auto& p_const = p;

  p.at(4U, 7U) = 123U;
  EXPECT_EQ(p_const.at(4U, 7U), 123U);
}
