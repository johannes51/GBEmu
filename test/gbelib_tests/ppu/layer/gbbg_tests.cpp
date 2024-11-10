#include "gtest/gtest.h"

#include "ppu/layer/gbbg.h"

#include "mock/mockregisteradapter.h"
#include "mock/mocktilemap.h"

TEST(GbBgTest, Construction) { EXPECT_NO_THROW(GbBg bg(nullptr, nullptr, nullptr, nullptr, nullptr)); }

TEST(GbBgTest, Draw)
{
  GbBg bg(nullptr, MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      std::make_unique<MockTileMap>());
  GbPixelBuffer i;
  EXPECT_NO_THROW(bg.draw(i));
}
