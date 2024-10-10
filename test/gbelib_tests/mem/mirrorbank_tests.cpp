#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/mirrorbank.h"
#include "mock/testbank.h"

using namespace std;

TEST(MirrorBankTest, Indirect)
{
  auto b = std::make_shared<TestBank>(MemoryArea { 0x0U, 0xFU });
  auto writeByte = b->getLocation(0x4U);
  uint8_t value = 0xA2U;
  *writeByte = value;

  MirrorBank m { { 0x10U, 0x1FU }, { 0x0U, 0xFU }, b };

  auto readByte = m.getLocation(0x10U + 0x4U)->getByte();
  EXPECT_EQ(value, readByte);

  *b->getLocation(0x5U) = value;
  EXPECT_EQ(0xA2A2U, m.getLocation(0x10U + 0x4U, true)->getWord());
}

TEST(MirrorBankTest, TooBig)
{
  auto b = std::make_shared<TestBank>(MemoryArea { 0, 15 });
  EXPECT_THROW(MirrorBank({ 16, 48 }, { 0, 15 }, b), std::invalid_argument);
}
