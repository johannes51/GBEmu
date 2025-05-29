#include "gtest/gtest.h"

#include "gb_factories/cartloader.h"

using namespace std;
using namespace gb;

TEST(CartloaderTest, Construction)
{
  EXPECT_NO_THROW(auto c = std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
}

TEST(CartloaderTest, Construct)
{
  std::vector<uint8_t> v(0x2FFFFU);
  auto c = std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav");

  EXPECT_NO_THROW(c->constructCart(v));
}

TEST(CartloaderTest, ConstructFail)
{
  std::vector<uint8_t> v(0xFFFFU);
  EXPECT_ANY_THROW((CartLoader("doesnt_exist.gb", "doesnt_exist.sav")));
}

TEST(CartloaderTest, Banks)
{
  auto c = std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav");
  std::vector<uint8_t> v(c->calculateNeccessarySize());
  auto b = c->constructCart(v);

  EXPECT_EQ(b->getBanks().getLocation8(0x0000U).get(), 0x3CU);
  EXPECT_EQ(b->getBanks().getLocation8(0x0001U).get(), 0xC9U);
  EXPECT_EQ(b->getBanks().getLocation8(0x0104U).get(), 0xCEU);
  EXPECT_EQ(b->getBanks().getLocation8(0x4000U).get(), 0xC3U);
}
