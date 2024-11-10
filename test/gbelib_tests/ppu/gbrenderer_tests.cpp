#include "gtest/gtest.h"

#include "ppu/gbrenderer.h"

class MockBg : public IBackground {
public:
  void draw(GbPixelBuffer& buffer) override { (void)buffer; }
};

class MockWin : public IWindow {
public:
  void draw(GbPixelBuffer& buffer) override { (void)buffer; }
};

class MockObj : public IObjects {
public:
  void draw(GbPixelBuffer& buffer) override { (void)buffer; }
};

TEST(GbRendererTest, Construction) { EXPECT_NO_THROW(GbRenderer r(nullptr, nullptr, nullptr)); }

TEST(GbRendererTest, Render)
{
  GbRenderer r(std::make_shared<MockBg>(), std::make_shared<MockWin>(), std::make_shared<MockObj>());
  GbPixelBuffer i;
  EXPECT_NO_THROW(r.render(i));
}
