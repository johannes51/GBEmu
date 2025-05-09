#include "gtest/gtest.h"

#include "ppu/layer/gbwindow.h"

#include "mock/mockregisteradapter.h"
#include "mock/mocktilemap.h"

TEST(GbWindowTest, Construction) { EXPECT_NO_THROW(GbWindow win(nullptr, nullptr, nullptr, nullptr, nullptr)); }

TEST(GbWindowTest, Draw)
{
  auto wx = MockRegisterAdapter::make(100);
  auto wy = MockRegisterAdapter::make(100);
  GbWindow win(
      MockRegisterAdapter::make(), wx, wy, MockRegisterAdapter::make(0b01101100U), std::make_unique<MockTileMap>());
  GbPixelBuffer b;

  EXPECT_NO_THROW(win.draw(b, 0U));
}
