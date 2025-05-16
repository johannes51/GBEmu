#include "gtest/gtest.h"

#include "ppu/layer/gbbg.h"
#include "ppu/layer/tilemap.h"

#include "mock/mockregisteradapter.h"
#include "mock/testbank.h"

// clang-format off
static const std::vector<uint8_t> TileSetData = {
  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
  0x01U, 0x01U, 0x06U, 0x07U, 0x0FU, 0x08U, 0x1FU, 0x10U,  0x1FU, 0x10U, 0x1FU, 0x10U, 0x17U, 0x1AU, 0x0AU, 0x0FU,
  0xC0U, 0xC0U, 0x30U, 0xF0U, 0x88U, 0x78U, 0xC4U, 0x3CU,  0xC4U, 0x3CU, 0xC4U, 0x3CU, 0xA4U, 0x7CU, 0x28U, 0xF8U,
  0x0FU, 0x08U, 0x05U, 0x06U, 0x0EU, 0x09U, 0x1FU, 0x14U,  0x1DU, 0x1EU, 0x05U, 0x07U, 0x03U, 0x03U, 0x00U, 0x00U,
  0xF8U, 0x08U, 0xD0U, 0x30U, 0x08U, 0xF8U, 0xD4U, 0x3CU,  0x9CU, 0x7CU, 0xD0U, 0xF0U, 0x60U, 0x60U, 0x00U, 0x00U,
};

static const std::vector<uint8_t> TileMapData = {
  0x01, 0x02, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x04,
  0x03, 0x04,
};
// clang-format on

TEST(GbBgTest, Construction)
{
  EXPECT_NO_THROW(GbBg bg(*(IRegisterAdapter*)nullptr, *(IRegisterAdapter*)nullptr, *(IRegisterAdapter*)nullptr,
      *(IRegisterAdapter*)nullptr, nullptr, nullptr));
}

TEST(GbBgTest, Draw)
{
  auto lcdc = MockRegisterAdapter::make(0b10000001U);
  auto mem = std::make_unique<TestBank>(MemoryArea { .from = 0x0000U, .to = 0xFFFFU });
  address_type add = 0x0U;
  for (add = 0x8000U; add <= 0x9FFFU; ++add) {
    mem->getLocation8(add) = 0U;
  }
  add = 0x9800U;
  for (address_type addoff = 0x0U; addoff < 32U * 32U; ++addoff) {
    mem->getLocation8(add + addoff) = 0U;
  }
  add = 0x8800U;
  for (const auto& tile : TileSetData) {
    mem->getLocation8(add++) = tile;
  }
  add = 0x9800U;
  for (const auto& tile : TileMapData) {
    mem->getLocation8(add++) = tile;
  }

  auto bgTm = std::make_unique<TileMap>(*lcdc, *mem, BgTileMapBit);
  auto scx = MockRegisterAdapter::make(0U);
  auto scy = MockRegisterAdapter::make(0U);
  auto bgp = MockRegisterAdapter::make(0b00011011U);
  GbBg bg(*lcdc, *scx, *scy, *bgp, std::make_unique<TileData>(*lcdc, *mem, BgWindowTileDataBit), std::move(bgTm));
  GbPixelBuffer b;

  for (uint16_t line = 0U; line < LcdHeight; ++line) {
    EXPECT_NO_THROW(bg.draw(b, line));
  }
  scx->setByte(4U);
  scy->setByte(6U);

  for (uint16_t line = 0U; line < LcdHeight; ++line) {
    EXPECT_NO_THROW(bg.draw(b, line));
  }
}
