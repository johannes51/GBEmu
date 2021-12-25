#include "gtest/gtest.h"

#include "ppu/layer/palette.h"

#include "mock/mockregisteradapter.h"

TEST(PaletteTests, Construction) { EXPECT_NO_THROW(Palette p(nullptr)); }

TEST(PaletteTests, Values)
{
  Palette p(MockRegisterAdapter::make());

  EXPECT_EQ(p.getColor(0b00), Colors::White);
  EXPECT_EQ(p.getColor(0b01), Colors::White);
  EXPECT_EQ(p.getColor(0b10), Colors::White);
  EXPECT_EQ(p.getColor(0b11), Colors::White);
}

TEST(PaletteTests, Exception)
{
  Palette p(MockRegisterAdapter::make());

  EXPECT_ANY_THROW(p.getColor(0b100));
}
