#include "gtest/gtest.h"

#include "location/location8.h"
#include "mem/registerbank.h"

using namespace std;

TEST(RegisterBankTest, Construction) { EXPECT_NO_THROW(RegisterBank b { 0x00 }); }

TEST(RegisterBankTest, Areas)
{
  RegisterBank b { 0x00 };
  ASSERT_EQ(1, b.availableAreas().size());
  EXPECT_EQ(0x00, b.availableAreas()[0].from);
  EXPECT_EQ(0x00, b.availableAreas()[0].to);
}

TEST(RegisterBankTest, Initial)
{
  uint8_t initial = 0xC4;
  address_type address = 0xFF3B;
  RegisterBank b { address, initial };
  EXPECT_EQ(initial, b.getLocation8(address)->get());
}

TEST(RegisterBankTest, Write8)
{
  RegisterBank b { 0, 0x16 };
  auto writeByte = b.getLocation8(0);
  uint8_t value = 0xA2;
  *writeByte = value;
  auto readByte = b.getLocation8(0);
  EXPECT_EQ(value, readByte->get());
}

TEST(RegisterBankTest, Write16)
{
  RegisterBank b { 0, 0x16 };
  EXPECT_ANY_THROW(b.getLocation16(0));
}

TEST(RegisterBankTest, Oob)
{
  RegisterBank b { 0 };
  EXPECT_ANY_THROW(b.getLocation8(4));
}
