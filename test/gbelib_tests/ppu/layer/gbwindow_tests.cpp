#include "gtest/gtest.h"

#include "ppu/layer/gbwindow.h"

#include "mock/mockregisteradapter.h"
#include "mock/mocktilemap.h"

TEST(GbWindowTest, Construction) { EXPECT_NO_THROW(GbWindow win(nullptr, nullptr, nullptr, nullptr, nullptr)); }

TEST(GbWindowTest, Draw)
{
  GbWindow win(nullptr, MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      std::make_unique<MockTileMap>());
  GbPixelBuffer i;
  EXPECT_NO_THROW(win.draw(i));
}
