#include "gtest/gtest.h"

#include "ppu/layer/tile.h"

TEST(TileTests, Construction) { EXPECT_NO_THROW(Tile t({})); }

TEST(TileTests, Get)
{
  Tile t({ 0b00011011, 0b01101100, 0b10110001, 0b11000110, 0b00011011, 0b01101100, 0b10110001, 0b11000110, 0b00011011,
      0b01101100, 0b10110001, 0b11000110, 0b00011011, 0b01101100, 0b10110001, 0b11000110 });

  EXPECT_EQ(t.get({ 0, 0 }), 0);
  EXPECT_EQ(t.get({ 1, 0 }), 1);
  EXPECT_EQ(t.get({ 2, 0 }), 2);
  EXPECT_EQ(t.get({ 3, 0 }), 3);

  EXPECT_EQ(t.get({ 0, 1 }), 2);
  EXPECT_EQ(t.get({ 1, 1 }), 3);
  EXPECT_EQ(t.get({ 2, 1 }), 0);
  EXPECT_EQ(t.get({ 3, 1 }), 1);
}
