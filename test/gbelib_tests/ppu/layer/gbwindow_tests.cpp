#include "gtest/gtest.h"

#include "ppu/layer/gbwindow.h"

#include "mock/mockregisteradapter.h"
#include "mock/mocktilemap.h"

TEST(GbWindowTest, Construction) { EXPECT_NO_THROW(GbWindow win(nullptr, nullptr, nullptr, nullptr, nullptr)); }

TEST(GbWindowTest, Draw)
{
  GbWindow win(nullptr, MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      std::make_unique<MockTileMap>());
  GbPixelBuffer b;

  EXPECT_NO_THROW(win.draw(b, 0U));
}
