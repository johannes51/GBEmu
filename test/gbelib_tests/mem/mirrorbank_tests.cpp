#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/mirrorbank.h"
#include "mock/testbank.h"

using namespace std;

TEST(MirrorBankTest, Indirect)
{
  auto b = std::make_shared<TestBank>(MemoryArea { 0, 15 });
  auto writeByte = b->getLocation(4);
  uint8_t value = 0xA2;
  *writeByte = value;

  MirrorBank m { { 16, 31 }, { 0, 15 }, b };

  auto readByte = m.getLocation(16 + 4)->getByte();
  EXPECT_EQ(value, readByte);
}

TEST(MirrorBankTest, TooBig)
{
  auto b = std::make_shared<TestBank>(MemoryArea { 0, 15 });
  EXPECT_THROW(MirrorBank({ 16, 48 }, { 0, 15 }, b), std::invalid_argument);
}
