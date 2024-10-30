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
