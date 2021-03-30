#include "gtest/gtest.h"

#include "gb_factories/cartloader.h"

using namespace std;
using namespace gb;

TEST(CartloaderTest, Construction) { EXPECT_NO_THROW(auto c = std::make_unique<CartLoader>("Tetris.gb")); }
