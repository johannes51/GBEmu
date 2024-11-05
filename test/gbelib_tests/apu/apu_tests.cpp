#include "gtest/gtest.h"

#include "apu/apu.h"

#include "mock/mockchannel.h"
#include "mock/mockmixer.h"
#include "mock/mockregisteradapter.h"

class ApuTests : public ::testing::Test {
public:
  ApuTests()
      : divApu(MockRegisterAdapter::make())
      , mockMixer()
      , ch1(MockChannel::make())
      , ch2(MockChannel::make())
      , ch3(MockChannel::make())
      , ch4(MockChannel::make())
  {
  }

protected:
  IRegisterAdapterSP divApu;
  IMixerUP mockMixer;
  ChannelSP ch1;
  ChannelSP ch2;
  ChannelSP ch3;
  ChannelSP ch4;

  void SetUp() override { mockMixer = MockMixer::make(); }
};

TEST(ApuTestsNF, Construction)
{
  EXPECT_ANY_THROW(
      Apu a(nullptr, { MockChannel::make(), MockChannel::make(), MockChannel::make(), MockChannel::make() },
          MockRegisterAdapter::make()));
  EXPECT_ANY_THROW(Apu a(MockMixer::make(),
      { MockChannel::make(), MockChannel::make(), MockChannel::make(), MockChannel::make() }, nullptr));
  EXPECT_ANY_THROW(Apu a(MockMixer::make(), {}, MockRegisterAdapter::make()));
  EXPECT_NO_THROW(
      Apu a(MockMixer::make(), { MockChannel::make(), MockChannel::make(), MockChannel::make(), MockChannel::make() },
          MockRegisterAdapter::make()));
}

TEST_F(ApuTests, Clock)
{
  Apu a(std::move(mockMixer), { ch1, ch2, ch3, ch4 }, divApu);
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  divApu->set(1U);
  EXPECT_NO_THROW(a.clock());
}

TEST_F(ApuTests, Sample)
{
  Apu a(std::move(mockMixer), { ch1, ch2, ch3, ch4 }, divApu);
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());

  EXPECT_DOUBLE_EQ(0., a.currentSample().first);
  EXPECT_DOUBLE_EQ(1., a.currentSample().second);

  divApu->set(1U);
  EXPECT_NO_THROW(a.clock());

  EXPECT_DOUBLE_EQ(0., a.currentSample().first);
  EXPECT_DOUBLE_EQ(1., a.currentSample().second);
}
