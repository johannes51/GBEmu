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
  std::vector<uint8_t> v(0xFFFFU);
  auto c = std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav");
  EXPECT_NO_THROW(c->constructBanks(v));
}

TEST(CartloaderTest, ConstructFail)
{
  std::vector<uint8_t> v(0xFFFFU);
  auto c = std::make_unique<CartLoader>("doesnt_exist.gb", "doesnt_exist.sav");
  EXPECT_ANY_THROW(c->constructBanks(v));
}

TEST(CartloaderTest, Banks)
{
  std::vector<uint8_t> v(0xFFFFU);
  auto c = std::make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav");
  auto b = c->constructBanks(v);

  EXPECT_EQ(b.size(), 3U);
  EXPECT_EQ(b[0]->getLocation8(0x0104U).get(), 0xCEU);
  EXPECT_EQ(b[1]->getLocation8(0x4000U).get(), 0xC3U);
}
