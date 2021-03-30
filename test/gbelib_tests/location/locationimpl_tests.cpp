#include "gtest/gtest.h"

#include "location/locationimpl.h"

#include "mock/variablebyte.h"

using namespace std;

class LocationImplMock : public LocationImpl {
public:
  LocationImplMock(LocationByteUP lower, LocationByteUP upper)
      : LocationImpl(std::move(lower), std::move(upper))
  {
  }
};

TEST(LocationImplTest, getByte)
{
  LocationImplMock a(make_unique<VariableByte>(5), make_unique<VariableByte>());
  EXPECT_EQ(a.getByte(), 5);
}

TEST(LocationImplTest, getWord1)
{
  LocationImplMock a(make_unique<VariableByte>(0xAB), make_unique<VariableByte>(0x5E));
  EXPECT_EQ(a.getWord(), 0x5EAB);
}

TEST(LocationImplTest, getWord2)
{
  LocationImplMock a(make_unique<VariableByte>(0xFF), make_unique<VariableByte>(0xFF));
  EXPECT_EQ(a.getWord(), 0xFFFF);
}
