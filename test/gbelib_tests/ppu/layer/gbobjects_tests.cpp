#include "gtest/gtest.h"

#include "ppu/layer/gbobjects.h"

TEST(GbgTest, Construction) { EXPECT_NO_THROW(GbObjects obj); }

TEST(GbgTest, Draw)
{
  GbObjects obj;
  IPixelBuffer i;
  EXPECT_NO_THROW(obj.draw(i));
}
