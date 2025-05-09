#include "gtest/gtest.h"

#include "mock/mockoam.h"
#include "mock/mockregisteradapter.h"
#include "mock/mocktiledata.h"

#include "ppu/layer/gbobjects.h"

TEST(GbgTest, Construction) { EXPECT_NO_THROW(GbObjects obj(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)); }

TEST(GbgTest, Draw)
{
  auto lcdc = MockRegisterAdapter::make(100);
  auto bgp = MockRegisterAdapter::make(100);

  auto data = std::array<uint8_t, 4> { 0b00001111, 0b00111111, 0b11111111, 0b00000011 };
  GbObjects obj { std::make_unique<MockOam>(std::vector { Object { std::span { data } } }), lcdc, nullptr, nullptr, bgp,
    std::make_unique<MockTileData>() };
  GbPixelBuffer b;

  EXPECT_NO_THROW(obj.draw(b, 0U));
}
