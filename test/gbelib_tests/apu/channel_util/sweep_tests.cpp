#include "gtest/gtest.h"

#include "apu/channel_util/sweep.h"

#include "mock/mockregisteradapter.h"

class SweepTests : public ::testing::Test {
public:
  SweepTests()
      : nr10(MockRegisterAdapter::make())
      , nr13(MockRegisterAdapter::make())
      , nr14(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterSP nr10;
  IRegisterAdapterSP nr13;
  IRegisterAdapterSP nr14;
};

TEST(SweepTestsNF, Construction)
{
  EXPECT_ANY_THROW(Sweep s(nullptr, nullptr, nullptr));
  EXPECT_NO_THROW(Sweep s(MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make()));
}

TEST_F(SweepTests, Direction)
{
  nr10->set(0b00101100U);
  nr13->set(0b11111111U);
  nr14->set(0b111U);

  Sweep s { nr10, nr13, nr14 };

  EXPECT_NO_THROW(s.clock());
  EXPECT_EQ(0b11111111U, nr13->get());
  EXPECT_NO_THROW(s.clock());
  EXPECT_LT(nr13->get(), 0b11111111U);

  nr10->set(0b00100100U);
  nr13->set(0b00000000U);

  EXPECT_NO_THROW(s.clock());
  EXPECT_EQ(0b00000000U, nr13->get());
  EXPECT_NO_THROW(s.clock());
  EXPECT_GT(nr13->get(), 0b00000000U);
}

TEST_F(SweepTests, Pace)
{
  nr10->set(0b00101100U);
  nr13->set(0b11111111U);
  nr14->set(0b111U);

  Sweep s { nr10, nr13, nr14 };

  ASSERT_NO_THROW(s.clock());
  ASSERT_EQ(0b11111111U, nr13->get());
  ASSERT_NO_THROW(s.clock());
  ASSERT_LT(nr13->get(), 0b11111111U);
  const auto p1 = nr13->get();

  nr10->set(0b00100010U);
  nr13->set(0b00000000U);

  ASSERT_NO_THROW(s.clock());
  ASSERT_EQ(0b00000000U, nr13->get());
  ASSERT_NO_THROW(s.clock());
  ASSERT_GT(nr13->get(), 0b00000000U);
  const auto p2 = nr13->get();

  EXPECT_LT(p1, p2);
}
