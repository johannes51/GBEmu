#include "gtest/gtest.h"

#include "ppu/layer/gbbg.h"

#include "mock/mockregisteradapter.h"
#include "mock/mocktilemap.h"

TEST(GbBgTest, Construction) { EXPECT_NO_THROW(GbBg bg(nullptr, nullptr, nullptr, nullptr, nullptr)); }

TEST(GbBgTest, Draw)
{
  auto scx = MockRegisterAdapter::make();
  auto scy = MockRegisterAdapter::make();
  GbBg bg(
      MockRegisterAdapter::make(), scx, scy, MockRegisterAdapter::make(0b00011011U), std::make_unique<MockTileMap>());
  GbPixelBuffer b;

  EXPECT_NO_THROW(bg.draw(b, 0U));
}
