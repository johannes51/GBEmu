#include "gtest/gtest.h"

#include "location/location.h"
#include "location/zerobyte.h"

TEST(LocationTest, testDereference1) {
  auto a = Location<uint8_t>::generate(std::make_unique<ZeroByte>());
  EXPECT_EQ(typeid(a->get()), typeid(uint8_t));
}

TEST(LocationTest, testDereference2) {
  auto a = Location<uint16_t>::generate(std::make_unique<ZeroByte>(), std::make_unique<ZeroByte>());
  EXPECT_EQ(typeid(a->get()), typeid(uint16_t));
}

TEST(LocationTest, testDereference3) {
  auto a = Location<uint16_t>::generate(std::make_unique<ZeroByte>());
  EXPECT_ANY_THROW(a->get());
}

