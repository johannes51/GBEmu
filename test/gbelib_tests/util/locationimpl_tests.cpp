#include "gtest/gtest.h"

#include "util/locationimpl.h"

#include "debug/variablelocation.h"


using namespace std;

class LocationImplMock : public LocationImpl
{
public:
  LocationImplMock(LocationByteUP lower, LocationByteUP upper)
    : LocationImpl(std::move(lower), std::move(upper)) {}
};

TEST(LocationImplTest, testgetByte) {
  auto a = LocationImplMock(make_unique<VariableLocation>(5), make_unique<VariableLocation>());
  ASSERT_EQ(a.getByte(), 5);
}

TEST(LocationImplTest, testgetWord1) {
  auto a = LocationImplMock(make_unique<VariableLocation>(0xAB), make_unique<VariableLocation>(0x5E));
  ASSERT_EQ(a.getWord(), 0x5EAB);
}

TEST(LocationImplTest, testgetWord2) {
  auto a = LocationImplMock(make_unique<VariableLocation>(0xFF), make_unique<VariableLocation>(0xFF));
  ASSERT_EQ(a.getWord(), 0xFFFF);
}

