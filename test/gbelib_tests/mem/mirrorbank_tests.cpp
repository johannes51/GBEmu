#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/mirrorbank.h"
#include "mem/rambank.h"

using namespace std;

TEST(MirrorBankTest, Indirect)
{
  auto b = std::make_shared<RamBank>(MemoryArea { 0, 15 });
  auto writeByte = b->getByte(4);
  uint8_t value = 0xA2;
  writeByte.set(value);

  MirrorBank m { { 16, 31 }, { 0, 15 }, b };

  auto readByte = m.getByte(16 + 4);
  EXPECT_EQ(value, readByte.get());
}

TEST(MirrorBankTest, TooBig)
{
  auto b = std::make_shared<RamBank>(MemoryArea { 0, 15 });
  EXPECT_THROW(MirrorBank({ 16, 48 }, { 0, 15 }, b), std::invalid_argument);
}
