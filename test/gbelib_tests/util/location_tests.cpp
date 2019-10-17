#include "gtest/gtest.h"

#include "util/location.h"

#include "debug/simplelocation.h"


using namespace std;

TEST(LocationTest, testDereference1) {
  auto a = Location<uint8_t>::generate(SimpleLocation());
  auto b = a.operator *();
  ASSERT_EQ(typeid(b), typeid(uint8_t));
}

TEST(LocationTest, testDereference2) {
  auto a = Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
  auto b = a.operator *();
  ASSERT_EQ(typeid(b), typeid(uint16_t));
}

TEST(LocationTest, testDereference3) {
  auto a = Location<uint16_t>::generate(SimpleLocation());
  ASSERT_ANY_THROW(a.operator *());
}

