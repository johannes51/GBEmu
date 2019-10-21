#include "gtest/gtest.h"

#include "location/locationimpl.h"

#include "debug/variablebyte.h"


using namespace std;

class LocationImplMock : public LocationImpl
{
public:
  LocationImplMock(LocationByteUP lower, LocationByteUP upper)
    : LocationImpl(std::move(lower), std::move(upper)) {}
};

TEST(LocationImplTest, testgetByte) {
  LocationImplMock a(make_unique<VariableByte>(5), make_unique<VariableByte>());
  ASSERT_EQ(a.getByte(), 5);
}

TEST(LocationImplTest, testgetWord1) {
  LocationImplMock a(make_unique<VariableByte>(0xAB), make_unique<VariableByte>(0x5E));
  ASSERT_EQ(a.getWord(), 0x5EAB);
}

TEST(LocationImplTest, testgetWord2) {
  LocationImplMock a(make_unique<VariableByte>(0xFF), make_unique<VariableByte>(0xFF));
  ASSERT_EQ(a.getWord(), 0xFFFF);
}

