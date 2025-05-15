#include "gtest/gtest.h"

#include "ppu/layer/gbwindow.h"

#include "mock/mockregisteradapter.h"
#include "mock/mocktiledata.h"
#include "mock/mocktilemap.h"

TEST(GbWindowTest, Construction)
{
  EXPECT_NO_THROW(GbWindow win(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr));
}

TEST(GbWindowTest, Draw)
{
  auto wx = MockRegisterAdapter::make(100U);
  auto wy = MockRegisterAdapter::make(100U);
  auto td = std::make_unique<MockTileData>(Tile{{
      0x7C, 0x7C, 0x00, 0xC6,
      0xC6, 0x00, 0x00, 0xFE,
      0xC6, 0xC6, 0x00, 0xC6,
      0xC6, 0x00, 0x00, 0x00
  }});
  GbWindow win(MockRegisterAdapter::make(0b10100001U), wx, wy, MockRegisterAdapter::make(0b01101100U), std::move(td), std::make_unique<MockTileMap>());
  GbPixelBuffer b;

  for (uint16_t line = 0U; line < LcdHeight; ++line) {
    EXPECT_NO_THROW(win.draw(b, line));
  }

  wx->set(10U);
  wy->set(2U);

  for (uint16_t line = 0U; line < LcdHeight; ++line) {
    EXPECT_NO_THROW(win.draw(b, line));
  }
}
