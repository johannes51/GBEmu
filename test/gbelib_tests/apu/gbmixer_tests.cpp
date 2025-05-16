#include "gtest/gtest.h"

#include "apu/gbmixer.h"

#include "mock/mockregisteradapter.h"

class GbMixerTests : public ::testing::Test {
public:
  GbMixerTests()
      : nr50(MockRegisterAdapter::make())
      , nr51(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterUP nr50;
  IRegisterAdapterUP nr51;
};

TEST(GbMixerTestsNF, Construction)
{
  EXPECT_NO_THROW(GbMixer c(*MockRegisterAdapter::make(), *MockRegisterAdapter::make()));
}

TEST_F(GbMixerTests, Mix)
{
  nr50->setByte(0b00011001U);
  nr51->setByte(0b11000011U);
  GbMixer c(*nr50, *nr51);

  const auto result = c.mix(1., 2., 4., 8., 16.);

  EXPECT_DOUBLE_EQ(19., result.first);
  EXPECT_DOUBLE_EQ(12., result.second);
}

TEST_F(GbMixerTests, MixTheOtherWay)
{
  nr50->setByte(0b10010001U);
  nr51->setByte(0b00111100U);
  GbMixer c(*nr50, *nr51);

  const auto result = c.mix(1., 2., 4., 8., 16.);

  EXPECT_DOUBLE_EQ(12., result.first);
  EXPECT_DOUBLE_EQ(19., result.second);
}
