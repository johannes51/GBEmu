#include "gtest/gtest.h"

#include "mock/mockoam.h"

#include "ppu/layer/gbobjects.h"

TEST(GbgTest, Construction) { EXPECT_NO_THROW(GbObjects obj(nullptr, nullptr, nullptr, nullptr, nullptr)); }

TEST(GbgTest, Draw)
{
  GbObjects obj(std::make_unique<MockOam>(), nullptr, nullptr, nullptr, nullptr);
  GbPixelBuffer i;
  EXPECT_NO_THROW(obj.draw(i));
}
