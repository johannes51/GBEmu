#include "gtest/gtest.h"

#include "debug/variablebyte.h"
#include "mem/rambank.h"
#include "location/location.h"
#include "location/zerobyte.h"

TEST(LocationTest, testGenerate1)
{
  auto a = Location<uint8_t>::generate(std::make_unique<ZeroByte>());
  EXPECT_EQ(typeid(a.get()), typeid(uint8_t));
}

TEST(LocationTest, testGenerate2)
{
  auto a = Location<uint16_t>::generate(std::make_unique<ZeroByte>(), std::make_unique<ZeroByte>());
  EXPECT_EQ(typeid(a.get()), typeid(uint16_t));
}

TEST(LocationTest, testGenerate3)
{
  auto a = Location<uint16_t>::generate(std::make_unique<ZeroByte>());
  EXPECT_ANY_THROW(a.get());
}

TEST(LocationTest, testFuse)
{
  RamBank bk({0, 2});
  bk.getWord(0).set(0x1E3F);
  auto a = bk.getByte(0);
  auto b = bk.getByte(1);
  auto c = Location<uint8_t>::fuse(std::move(a), std::move(b));
  EXPECT_EQ(typeid(uint16_t), typeid(c.get()));
  EXPECT_EQ(0x1E3F, c.get());
}
