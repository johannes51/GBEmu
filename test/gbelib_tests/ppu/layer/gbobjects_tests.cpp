#include "gtest/gtest.h"

#include "mock/mockoam.h"
#include "mock/mockregisteradapter.h"
#include "mock/mocktiledata.h"

#include "ppu/layer/gbobjects.h"

TEST(GbObjectsTest, Construction)
{
  EXPECT_NO_THROW(GbObjects obj(nullptr, *MockRegisterAdapter::make(), *(IRegisterAdapter*)nullptr,
      *(IRegisterAdapter*)nullptr, *MockRegisterAdapter::make(), nullptr));
}

TEST(GbObjectsTest, Draw)
{
  auto lcdc = MockRegisterAdapter::make(0b10000011U);
  auto bgp = MockRegisterAdapter::make(0b01101100U);
  auto data = std::array<uint8_t, 4> { 0b00001111, 0b00111111, 0b11111111, 0b00000011 };
  GbObjects obj { std::make_unique<MockOam>(std::vector { Object { std::span { data } } }), *lcdc,
    *(IRegisterAdapter*)nullptr, *(IRegisterAdapter*)nullptr, *bgp, std::make_unique<MockTileData>() };
  GbPixelBuffer b;

  for (uint16_t line = 0U; line < LcdHeight; ++line) {
    EXPECT_NO_THROW(obj.draw(b, line));
  }
}
