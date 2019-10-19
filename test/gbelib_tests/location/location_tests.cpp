#include "gtest/gtest.h"

#include "location/location.h"

#include "debug/simplelocation.h"


using namespace std;

TEST(LocationTest, testDereference1) {
  auto a = Location<uint8_t>::generate(std::make_unique<SimpleLocation>());
  ASSERT_EQ(typeid(**a), typeid(uint8_t));
}

TEST(LocationTest, testDereference2) {
  auto a = Location<uint16_t>::generate(std::make_unique<SimpleLocation>(), std::make_unique<SimpleLocation>());
  ASSERT_EQ(typeid(**a), typeid(uint16_t));
}

TEST(LocationTest, testDereference3) {
  auto a = Location<uint16_t>::generate(std::make_unique<SimpleLocation>());
  ASSERT_ANY_THROW(**a);
}

