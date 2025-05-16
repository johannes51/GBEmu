#include "gtest/gtest.h"

#include "apu/gbchannel4.h"

#include "AudioFile.h"

#include "mock/mockregisteradapter.h"

class GbChannel4Tests : public ::testing::Test {
public:
  GbChannel4Tests()
      : nr41(MockRegisterAdapter::make())
      , nr42(MockRegisterAdapter::make())
      , nr43(MockRegisterAdapter::make())
      , nr44(MockRegisterAdapter::make())
      , nr52(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterUP nr41;
  IRegisterAdapterUP nr42;
  IRegisterAdapterUP nr43;
  IRegisterAdapterUP nr44;
  IRegisterAdapterUP nr52;
};

TEST(GbChannel4TestsNF, Construction)
{
  EXPECT_NO_THROW(GbChannel4 c(*MockRegisterAdapter::make(), *MockRegisterAdapter::make(), *MockRegisterAdapter::make(),
      *MockRegisterAdapter::make(), *MockRegisterAdapter::make()));
}

TEST_F(GbChannel4Tests, Wav)
{
  nr52->setByte(0b10001000U);
  nr43->setByte(0b01010000U);
  nr44->setByte(0b11000111U);
  nr42->setByte(0b11110001U);
  nr41->setByte(0b10000011U);
  GbChannel4 c(*nr41, *nr42, *nr43, *nr44, *nr52);

  AudioFile<double> a1 {};
  a1.setBitDepth(16);
  a1.setNumChannels(1);
  a1.setSampleRate(44100);
  a1.setNumSamplesPerChannel(1.5 * 44100);

  auto frameSequencer = 0U;
  for (auto i = 0U; i < 1048576; ++i) {
    c.clock();
    if (i % (1048576 / 44100) == 0) {
      a1.samples[0][i / (1048576 / 44100)] = c.getSample();
    }
    if ((i & 0b111111111111U) == 0b100000000000U) {
      c.tickApuDiv(static_cast<FrameSequence>(frameSequencer++));
      if (frameSequencer > 7U) {
        frameSequencer = 0U;
      }
    }
  }
  a1.save("bla5.wav");

  nr52->setByte(0b10001000U);
  nr43->setByte(0b01011000U);
  nr44->setByte(0b11000111U);
  nr42->setByte(0b11110001U);
  nr41->setByte(0b10000011U);

  AudioFile<double> a2 {};
  a2.setBitDepth(16);
  a2.setNumChannels(1);
  a2.setSampleRate(44100);
  a2.setNumSamplesPerChannel(1.5 * 44100);

  frameSequencer = 0U;
  for (auto i = 0U; i < 1048576; ++i) {
    c.clock();
    if (i % (1048576 / 44100) == 0) {
      a2.samples[0][i / (1048576 / 44100)] = c.getSample();
    }
    if ((i & 0b111111111111U) == 0b100000000000U) {
      c.tickApuDiv(static_cast<FrameSequence>(frameSequencer++));
      if (frameSequencer > 7U) {
        frameSequencer = 0U;
      }
    }
  }
  a2.save("bla5-2.wav");
}
