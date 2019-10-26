#include "gtest/gtest.h"

#include "location/location.h"
#include "location/rambyte.h"
#include "util/ops.h"

TEST(OpsTest, testIncrement8)
{
  uint8_t buffer = 5;
  auto l = Location<uint8_t>::generate(std::make_unique<RamByte>(buffer));

  ops::increment(std::move(l));

  EXPECT_EQ(6, buffer);
}

TEST(OpsTest, testIncrement16)
{
  uint8_t bufferL = 0xFF;
  uint8_t bufferU = 0xAF;
  auto l = Location<uint16_t>::generate(std::make_unique<RamByte>(bufferL), std::make_unique<RamByte>(bufferU));

  ops::increment(std::move(l));

  EXPECT_EQ(0x00, bufferL);
  EXPECT_EQ(0xB0, bufferU);
}

TEST(OpsTest, testAdd8)
{
  uint8_t a = 5;
  uint8_t b = 13;
  auto lA = Location<uint8_t>::generate(std::make_unique<RamByte>(a));
  auto lB = Location<uint8_t>::generate(std::make_unique<RamByte>(b));

  ops::add(std::move(lA), std::move(lB));

  EXPECT_EQ(5 + 13, a);
}

TEST(OpsTest, testAdd16)
{
  uint8_t aL = 0x35;
  uint8_t bL = 0xA2;
  uint8_t aU = 0x14;
  uint8_t bU = 0xC7;
  auto lA = Location<uint16_t>::generate(std::make_unique<RamByte>(aL), std::make_unique<RamByte>(aU));
  auto lB = Location<uint16_t>::generate(std::make_unique<RamByte>(bL), std::make_unique<RamByte>(bU));

  ops::add(std::move(lA), std::move(lB));

  EXPECT_EQ(0x35 + 0xA2, aL);
  EXPECT_EQ(0x14 + 0xC7, aU);
}

TEST(OpsTest, testLoad8)
{
  uint8_t dest = 0x3C;
  uint8_t src = 0xF1;
  auto d = Location<uint8_t>::generate(std::make_unique<RamByte>(dest));
  auto s = Location<uint8_t>::generate(std::make_unique<RamByte>(src));

  ops::load(std::move(d), std::move(s));

  EXPECT_EQ(0xF1, dest);
}

TEST(OpsTest, testLoad16)
{
  uint8_t destL = 0x3C;
  uint8_t destU = 0xB8;
  uint8_t srcL = 0xF1;
  uint8_t srcU = 0xC3;
  auto d = Location<uint16_t>::generate(std::make_unique<RamByte>(destL), std::make_unique<RamByte>(destU));
  auto s = Location<uint16_t>::generate(std::make_unique<RamByte>(srcL), std::make_unique<RamByte>(srcU));

  ops::load(std::move(d), std::move(s));

  EXPECT_EQ(0xF1, destL);
  EXPECT_EQ(0xC3, destU);
}
