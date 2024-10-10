#include "gtest/gtest.h"

#include "location/location.h"

#include "mem/rambank.h"

TEST(LocationTest, Fuse)
{
  std::vector<uint8_t> v { 0U, 16 };
  RamBank bk({ 0, 16 }, v);
  *bk.getLocation(0, true) = uint16_t { 0x1E3F };

  auto a = bk.getLocation(0);
  auto b = bk.getLocation(1);

  EXPECT_FALSE(a->isWord());
  EXPECT_EQ(0x3FU, a->get<uint8_t>());

  a->fuse(*b);
  EXPECT_TRUE(a->isWord());
  EXPECT_EQ(0x1E3FU, a->get<uint16_t>());
}
