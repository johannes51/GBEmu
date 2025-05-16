#include "gtest/gtest.h"

#include "apu/channel_util/period.h"

#include "mock/mockregisteradapter.h"

class PeriodTests : public ::testing::Test {
public:
  PeriodTests()
      : nrX3(MockRegisterAdapter::make())
      , nrX4(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterUP nrX3;
  IRegisterAdapterUP nrX4;
};

TEST(PeriodTestsNF, Construction)
{
  EXPECT_NO_THROW(Period p(*MockRegisterAdapter::make(), *MockRegisterAdapter::make()));
}

TEST_F(PeriodTests, Done)
{
  nrX3->setByte(0b11111100U);
  nrX4->setByte(0b111U);

  Period p { *nrX3, *nrX4 };

  EXPECT_FALSE(p.clockIsDone());
  EXPECT_FALSE(p.clockIsDone());
  EXPECT_FALSE(p.clockIsDone());
  EXPECT_TRUE(p.clockIsDone());
}

TEST_F(PeriodTests, Restart)
{
  nrX3->setByte(0b11111100U);
  nrX4->setByte(0b111U);

  Period p { *nrX3, *nrX4 };

  ASSERT_FALSE(p.clockIsDone());
  ASSERT_FALSE(p.clockIsDone());
  ASSERT_FALSE(p.clockIsDone());
  ASSERT_TRUE(p.clockIsDone());

  EXPECT_FALSE(p.clockIsDone());
  EXPECT_FALSE(p.clockIsDone());
  EXPECT_FALSE(p.clockIsDone());
  EXPECT_TRUE(p.clockIsDone());
}
