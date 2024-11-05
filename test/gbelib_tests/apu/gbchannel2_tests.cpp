#include "gtest/gtest.h"

#include "apu/gbchannel2.h"

#include "AudioFile.h"

#include "mock/mockregisteradapter.h"

class GbChannel2Tests : public ::testing::Test {
public:
  GbChannel2Tests()
      : nr21(MockRegisterAdapter::make())
      , nr22(MockRegisterAdapter::make())
      , nr23(MockRegisterAdapter::make())
      , nr24(MockRegisterAdapter::make())
      , nr52(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterSP nr21;
  IRegisterAdapterSP nr22;
  IRegisterAdapterSP nr23;
  IRegisterAdapterSP nr24;
  IRegisterAdapterSP nr52;
};

TEST(GbChannel2TestsNF, Construction)
{
  EXPECT_ANY_THROW(GbChannel2 c(nullptr, nullptr, nullptr, nullptr, nullptr));
  EXPECT_NO_THROW(GbChannel2 c(MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      MockRegisterAdapter::make(), MockRegisterAdapter::make()));
}

TEST_F(GbChannel2Tests, Wav)
{
  nr52->set(0b10000010U);
  nr23->set(0b11010000U);
  nr24->set(0b11000111U);
  nr22->set(0b11110001U);
  nr21->set(0b10000011U);
  GbChannel2 c(nr21, nr22, nr23, nr24, nr52);

  AudioFile<double> a {};
  a.setBitDepth(16);
  a.setNumChannels(1);
  a.setSampleRate(44100);
  a.setNumSamplesPerChannel(1.5 * 44100);

  auto frameSequencer = 0U;
  for (auto i = 0U; i < 1048576; ++i) {
    c.clock();
    auto bla2 = i % (1048576 / 44100);
    auto bla3 = i / (1048576 / 44100);
    if (bla2 == 0) {
      a.samples[0][bla3] = c.getSample();
    }
    if ((i & 0b111111111111U) == 0b100000000000U) {
      c.tickApuDiv(static_cast<FrameSequence>(frameSequencer++));
      if (frameSequencer > 7U) {
        frameSequencer = 0U;
      }
    }
  }
  a.save("bla.wav");
}
