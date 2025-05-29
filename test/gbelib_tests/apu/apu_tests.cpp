#include "gtest/gtest.h"

#include "apu/apu.h"

#include "mock/mockchannel.h"
#include "mock/mockmixer.h"
#include "mock/mockregisteradapter.h"

class ApuTests : public ::testing::Test {
public:
  ApuTests()
      : mockMixer()
      , ch1()
      , ch2()
      , ch3()
      , ch4()
  {
  }

protected:
  IMixerUP mockMixer;
  ChannelUP ch1;
  ChannelUP ch2;
  ChannelUP ch3;
  ChannelUP ch4;

  void SetUp() override
  {
    mockMixer = MockMixer::make();
    ch1 = MockChannel::make();
    ch2 = MockChannel::make();
    ch3 = MockChannel::make();
    ch4 = MockChannel::make();
  }
};

TEST(ApuTestsNF, Construction)
{
  EXPECT_NO_THROW(Apu a{});
}

TEST_F(ApuTests, Clock)
{
  Apu a{};
  a.setMixer(std::move(mockMixer));
  a.addChannel(std::move(ch1));
  a.addChannel(std::move(ch2));
  a.addChannel(std::move(ch3));
  a.addChannel(std::move(ch4));
  auto& divApu = a.getDivApu();

  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());

  divApu.setByte(1U);
  EXPECT_NO_THROW(a.clock());
}

TEST_F(ApuTests, Sample)
{
  Apu a{};
  a.setMixer(std::move(mockMixer));
  a.addChannel(std::move(ch1));
  a.addChannel(std::move(ch2));
  a.addChannel(std::move(ch3));
  a.addChannel(std::move(ch4));
  auto& divApu = a.getDivApu();

  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());
  EXPECT_NO_THROW(a.clock());

  EXPECT_DOUBLE_EQ(0., a.currentSample().first);
  EXPECT_DOUBLE_EQ(1., a.currentSample().second);

  divApu.setByte(1U);
  EXPECT_NO_THROW(a.clock());

  EXPECT_DOUBLE_EQ(0., a.currentSample().first);
  EXPECT_DOUBLE_EQ(1., a.currentSample().second);
}
