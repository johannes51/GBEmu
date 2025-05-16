#include "gtest/gtest.h"

#include "ppu/layer/gbpalette.h"

#include "mock/mockregisteradapter.h"

TEST(GbPaletteTests, Construction) { EXPECT_NO_THROW(GbPalette p(*MockRegisterAdapter::make())); }

TEST(GbPaletteTests, Values)
{
  auto bgp = MockRegisterAdapter::make();
  GbPalette p(*bgp);

  EXPECT_EQ(p.getColor(0b00), GbColors::White);
  EXPECT_EQ(p.getColor(0b01), GbColors::White);
  EXPECT_EQ(p.getColor(0b10), GbColors::White);
  EXPECT_EQ(p.getColor(0b11), GbColors::White);

  bgp->setByte(0b10011100);

  EXPECT_EQ(p.getColor(0b00), GbColors::White);
  EXPECT_EQ(p.getColor(0b01), GbColors::Black);
  EXPECT_EQ(p.getColor(0b10), GbColors::LightGray);
  EXPECT_EQ(p.getColor(0b11), GbColors::DarkGray);
}

TEST(GbPaletteTests, Exception)
{
  GbPalette p(*MockRegisterAdapter::make());

  EXPECT_ANY_THROW(p.getColor(0b100));
}
