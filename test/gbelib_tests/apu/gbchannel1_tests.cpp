#include "gtest/gtest.h"

#include "apu/gbchannel1.h"

#include "AudioFile.h"

#include "mock/mockregisteradapter.h"

class GbChannel1Tests : public ::testing::Test {
public:
  GbChannel1Tests()
      : nr10(MockRegisterAdapter::make())
      , nr11(MockRegisterAdapter::make())
      , nr12(MockRegisterAdapter::make())
      , nr13(MockRegisterAdapter::make())
      , nr14(MockRegisterAdapter::make())
      , nr52(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterSP nr10;
  IRegisterAdapterSP nr11;
  IRegisterAdapterSP nr12;
  IRegisterAdapterSP nr13;
  IRegisterAdapterSP nr14;
  IRegisterAdapterSP nr52;
};

TEST(GbChannel1TestsNF, Construction)
{
  EXPECT_ANY_THROW(GbChannel1 c(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr));
  EXPECT_NO_THROW(GbChannel1 c(MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make()));
}

TEST_F(GbChannel1Tests, Wav)
{
  nr52->set(0b10000010U);
  nr13->set(0b11000000U);
  nr14->set(0b11000111U);
  nr12->set(0b11110001U);
  nr11->set(0b10000111U);
  nr10->set(0b000101011);
  GbChannel1 c(nr10, nr11, nr12, nr13, nr14, nr52);

  AudioFile<double> a {};
  a.setBitDepth(16);
  a.setNumChannels(1);
  a.setSampleRate(44100);
  a.setNumSamplesPerChannel(1.5 * 44100);

  auto frameSequencer = 0U;
  for (auto i = 0U; i < 1048576; ++i) {
    c.clock();
    auto bla = (1048576 / 44100);
    auto bla2 = i % (1048576 / 44100);
    auto bla3 = i / (1048576 / 44100);
    if (bla2 == 0) {
      a.samples[0][bla3] = c.getSample();
    }
    if ((i & 0b111111111111U) == 0b100000000000U) {
      c.tickApuDiv(frameSequencer++);
      if (frameSequencer > 7U) {
        frameSequencer = 0U;
      }
    }
  }
  a.save("bla3.wav");

  AudioFile<short> a2 {};
  a2.setBitDepth(16);
  a2.setNumChannels(2);
  a2.setSampleRate(44100);
  a2.setNumSamplesPerChannel(2 * 1048576);
}
