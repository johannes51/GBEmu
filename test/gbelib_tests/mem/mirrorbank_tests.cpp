#include "gtest/gtest.h"

#include "mem/common/mirrorbank.h"
#include "mem/ilocation8.h"
#include "mock/testbank.h"

using namespace std;

TEST(MirrorBankTest, Indirect)
{
  auto b = std::make_unique<TestBank>(MemoryArea { 0x0U, 0xFU });
  auto& writeByte = b->getLocation8(0x4U);
  uint8_t value = 0xA2U;
  writeByte = value;

  MirrorBank m { { 0x10U, 0x1FU }, { 0x0U, 0xFU }, *b };

  auto readByte = m.getLocation8(0x10U + 0x4U).get();
  EXPECT_EQ(value, readByte);
}

TEST(MirrorBankTest, TooBig)
{
  auto b = std::make_unique<TestBank>(MemoryArea { 0, 15 });
  EXPECT_THROW(MirrorBank({ 16, 48 }, { 0, 15 }, *b), std::invalid_argument);
}
