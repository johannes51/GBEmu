#include "gtest/gtest.h"

#include "ppu/layer/tile.h"

TEST(TileTests, Construction) { EXPECT_NO_THROW(Tile t({})); }

TEST(TileTests, Get)
{
  Tile t({ 0x7CU, 0x7CU, 0x00U, 0xC6U, 0xC6U, 0x00U, 0x00U, 0xFEU, 0xC6U, 0xC6U, 0x00U, 0xC6U, 0xC6U, 0x00U, 0x00U,
      0x00U });

  EXPECT_EQ(0U, t.get({ 0, 0 }));
  EXPECT_EQ(3U, t.get({ 1, 0 }));
  EXPECT_EQ(3U, t.get({ 2, 0 }));
  EXPECT_EQ(3U, t.get({ 3, 0 }));
  EXPECT_EQ(3U, t.get({ 4, 0 }));
  EXPECT_EQ(3U, t.get({ 5, 0 }));
  EXPECT_EQ(0U, t.get({ 6, 0 }));
  EXPECT_EQ(0U, t.get({ 7, 0 }));

  EXPECT_EQ(2U, t.get({ 0, 1 }));
  EXPECT_EQ(2U, t.get({ 1, 1 }));
  EXPECT_EQ(0U, t.get({ 2, 1 }));
  EXPECT_EQ(0U, t.get({ 3, 1 }));
  EXPECT_EQ(0U, t.get({ 4, 1 }));
  EXPECT_EQ(2U, t.get({ 5, 1 }));
  EXPECT_EQ(2U, t.get({ 6, 1 }));
  EXPECT_EQ(0U, t.get({ 7, 1 }));

  EXPECT_EQ(1U, t.get({ 0, 2 }));
  EXPECT_EQ(1U, t.get({ 1, 2 }));
  EXPECT_EQ(0U, t.get({ 2, 2 }));
  EXPECT_EQ(0U, t.get({ 3, 2 }));
  EXPECT_EQ(0U, t.get({ 4, 2 }));
  EXPECT_EQ(1U, t.get({ 5, 2 }));
  EXPECT_EQ(1U, t.get({ 6, 2 }));
  EXPECT_EQ(0U, t.get({ 7, 2 }));

  EXPECT_EQ(2U, t.get({ 0, 3 }));
  EXPECT_EQ(2U, t.get({ 1, 3 }));
  EXPECT_EQ(2U, t.get({ 2, 3 }));
  EXPECT_EQ(2U, t.get({ 3, 3 }));
  EXPECT_EQ(2U, t.get({ 4, 3 }));
  EXPECT_EQ(2U, t.get({ 5, 3 }));
  EXPECT_EQ(2U, t.get({ 6, 3 }));
  EXPECT_EQ(0U, t.get({ 7, 3 }));

  EXPECT_EQ(3U, t.get({ 0, 4 }));
  EXPECT_EQ(3U, t.get({ 1, 4 }));
  EXPECT_EQ(0U, t.get({ 2, 4 }));
  EXPECT_EQ(0U, t.get({ 3, 4 }));
  EXPECT_EQ(0U, t.get({ 4, 4 }));
  EXPECT_EQ(3U, t.get({ 5, 4 }));
  EXPECT_EQ(3U, t.get({ 6, 4 }));
  EXPECT_EQ(0U, t.get({ 7, 4 }));

  EXPECT_EQ(2U, t.get({ 0, 5 }));
  EXPECT_EQ(2U, t.get({ 1, 5 }));
  EXPECT_EQ(0U, t.get({ 2, 5 }));
  EXPECT_EQ(0U, t.get({ 3, 5 }));
  EXPECT_EQ(0U, t.get({ 4, 5 }));
  EXPECT_EQ(2U, t.get({ 5, 5 }));
  EXPECT_EQ(2U, t.get({ 6, 5 }));
  EXPECT_EQ(0U, t.get({ 7, 5 }));

  EXPECT_EQ(1U, t.get({ 0, 6 }));
  EXPECT_EQ(1U, t.get({ 1, 6 }));
  EXPECT_EQ(0U, t.get({ 2, 6 }));
  EXPECT_EQ(0U, t.get({ 3, 6 }));
  EXPECT_EQ(0U, t.get({ 4, 6 }));
  EXPECT_EQ(1U, t.get({ 5, 6 }));
  EXPECT_EQ(1U, t.get({ 6, 6 }));
  EXPECT_EQ(0U, t.get({ 7, 6 }));

  EXPECT_EQ(0U, t.get({ 0, 7 }));
  EXPECT_EQ(0U, t.get({ 1, 7 }));
  EXPECT_EQ(0U, t.get({ 2, 7 }));
  EXPECT_EQ(0U, t.get({ 3, 7 }));
  EXPECT_EQ(0U, t.get({ 4, 7 }));
  EXPECT_EQ(0U, t.get({ 5, 7 }));
  EXPECT_EQ(0U, t.get({ 6, 7 }));
  EXPECT_EQ(0U, t.get({ 7, 7 }));
}

TEST(TileTests, Get2)
{
  Tile t({
      0xC0U,
      0xC7U,
      0xC0U,
      0x83U,
      0x20U,
      0x05U,
      0x10U,
      0x08U,
      0x08U,
      0x10U,
      0x05U,
      0xA1U,
      0x03U,
      0xC1U,
      0x07U,
      0xE7U,
  });

  EXPECT_EQ(3U, t.get({ 0, 0 }));
  EXPECT_EQ(3U, t.get({ 1, 0 }));
  EXPECT_EQ(0U, t.get({ 2, 0 }));
  EXPECT_EQ(0U, t.get({ 3, 0 }));
  EXPECT_EQ(0U, t.get({ 4, 0 }));
  EXPECT_EQ(2U, t.get({ 5, 0 }));
  EXPECT_EQ(2U, t.get({ 6, 0 }));
  EXPECT_EQ(2U, t.get({ 7, 0 }));

  EXPECT_EQ(3U, t.get({ 0, 1 }));
  EXPECT_EQ(1U, t.get({ 1, 1 }));
  EXPECT_EQ(0U, t.get({ 2, 1 }));
  EXPECT_EQ(0U, t.get({ 3, 1 }));
  EXPECT_EQ(0U, t.get({ 4, 1 }));
  EXPECT_EQ(0U, t.get({ 5, 1 }));
  EXPECT_EQ(2U, t.get({ 6, 1 }));
  EXPECT_EQ(2U, t.get({ 7, 1 }));

  EXPECT_EQ(0U, t.get({ 0, 2 }));
  EXPECT_EQ(0U, t.get({ 1, 2 }));
  EXPECT_EQ(1U, t.get({ 2, 2 }));
  EXPECT_EQ(0U, t.get({ 3, 2 }));
  EXPECT_EQ(0U, t.get({ 4, 2 }));
  EXPECT_EQ(2U, t.get({ 5, 2 }));
  EXPECT_EQ(0U, t.get({ 6, 2 }));
  EXPECT_EQ(2U, t.get({ 7, 2 }));

  EXPECT_EQ(0U, t.get({ 0, 3 }));
  EXPECT_EQ(0U, t.get({ 1, 3 }));
  EXPECT_EQ(0U, t.get({ 2, 3 }));
  EXPECT_EQ(1U, t.get({ 3, 3 }));
  EXPECT_EQ(2U, t.get({ 4, 3 }));
  EXPECT_EQ(0U, t.get({ 5, 3 }));
  EXPECT_EQ(0U, t.get({ 6, 3 }));
  EXPECT_EQ(0U, t.get({ 7, 3 }));

  EXPECT_EQ(0U, t.get({ 0, 4 }));
  EXPECT_EQ(0U, t.get({ 1, 4 }));
  EXPECT_EQ(0U, t.get({ 2, 4 }));
  EXPECT_EQ(2U, t.get({ 3, 4 }));
  EXPECT_EQ(1U, t.get({ 4, 4 }));
  EXPECT_EQ(0U, t.get({ 5, 4 }));
  EXPECT_EQ(0U, t.get({ 6, 4 }));
  EXPECT_EQ(0U, t.get({ 7, 4 }));

  EXPECT_EQ(2U, t.get({ 0, 5 }));
  EXPECT_EQ(0U, t.get({ 1, 5 }));
  EXPECT_EQ(2U, t.get({ 2, 5 }));
  EXPECT_EQ(0U, t.get({ 3, 5 }));
  EXPECT_EQ(0U, t.get({ 4, 5 }));
  EXPECT_EQ(1U, t.get({ 5, 5 }));
  EXPECT_EQ(0U, t.get({ 6, 5 }));
  EXPECT_EQ(3U, t.get({ 7, 5 }));

  EXPECT_EQ(2U, t.get({ 0, 6 }));
  EXPECT_EQ(2U, t.get({ 1, 6 }));
  EXPECT_EQ(0U, t.get({ 2, 6 }));
  EXPECT_EQ(0U, t.get({ 3, 6 }));
  EXPECT_EQ(0U, t.get({ 4, 6 }));
  EXPECT_EQ(0U, t.get({ 5, 6 }));
  EXPECT_EQ(1U, t.get({ 6, 6 }));
  EXPECT_EQ(3U, t.get({ 7, 6 }));

  EXPECT_EQ(2U, t.get({ 0, 7 }));
  EXPECT_EQ(2U, t.get({ 1, 7 }));
  EXPECT_EQ(2U, t.get({ 2, 7 }));
  EXPECT_EQ(0U, t.get({ 3, 7 }));
  EXPECT_EQ(0U, t.get({ 4, 7 }));
  EXPECT_EQ(3U, t.get({ 5, 7 }));
  EXPECT_EQ(3U, t.get({ 6, 7 }));
  EXPECT_EQ(3U, t.get({ 7, 7 }));
}
