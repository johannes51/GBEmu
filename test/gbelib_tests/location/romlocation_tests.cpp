#include "gtest/gtest.h"

#include "mem/rambank.h"

#include "location/romlocation.h"

TEST(RomLocationTest, Read)
{
  std::vector<uint8_t> buffer = { 0x4E };
  RamBank b { { 0, 2 }, buffer };
  RomLocation a { Location::Type::Single, b, 0 };

  EXPECT_EQ(buffer[0], a.getByte());
}

TEST(RomLocationTest, Write)
{
  std::vector<uint8_t> buffer = { 0x4E };
  RamBank b { { 0, 2 }, buffer };
  RomLocation a { Location::Type::Single, b, 0 };

  EXPECT_ANY_THROW(a = uint8_t(0));
  EXPECT_ANY_THROW(a = uint16_t(0));
}
