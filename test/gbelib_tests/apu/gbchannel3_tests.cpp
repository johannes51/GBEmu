#include "gtest/gtest.h"

#include "apu/gbchannel3.h"

#include "AudioFile.h"

#include "mock/mockregisteradapter.h"
#include "mock/testbank.h"

class GbChannel3Tests : public ::testing::Test {
public:
  GbChannel3Tests()
      : nr30(MockRegisterAdapter::make())
      , nr31(MockRegisterAdapter::make())
      , nr32(MockRegisterAdapter::make())
      , nr33(MockRegisterAdapter::make())
      , nr34(MockRegisterAdapter::make())
      , nr52(MockRegisterAdapter::make())
      , waveRam(std::make_shared<TestBank>(MemoryArea { 0xFF30U, 0xFF3FU }))
  {
  }

protected:
  IRegisterAdapterSP nr30;
  IRegisterAdapterSP nr31;
  IRegisterAdapterSP nr32;
  IRegisterAdapterSP nr33;
  IRegisterAdapterSP nr34;
  IRegisterAdapterSP nr52;
  IMemoryViewSP waveRam;
};

TEST(GbChannel3TestsNF, Construction)
{
  EXPECT_ANY_THROW(GbChannel3 c(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr));
  EXPECT_ANY_THROW(GbChannel3 c(MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(), nullptr));
  EXPECT_NO_THROW(GbChannel3 c(MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      std::make_shared<TestBank>(MemoryArea { 0xFF30U, 0xFF3FU })));
}

TEST_F(GbChannel3Tests, Wav)
{
  nr52->set(0b10000010U);
  nr33->set(0b01010000U);
  nr34->set(0b11000111U);
  nr32->set(0b01100000U);
  nr31->set(0b10000011U);
  *waveRam->getLocation(0xFF30) = std::uint8_t { 0xFA };
  *waveRam->getLocation(0xFF31) = std::uint8_t { 0x00 };
  *waveRam->getLocation(0xFF32) = std::uint8_t { 0xAF };
  *waveRam->getLocation(0xFF33) = std::uint8_t { 0xFA };
  *waveRam->getLocation(0xFF34) = std::uint8_t { 0x00 };
  *waveRam->getLocation(0xFF35) = std::uint8_t { 0xAF };
  *waveRam->getLocation(0xFF36) = std::uint8_t { 0xFA };
  *waveRam->getLocation(0xFF37) = std::uint8_t { 0x00 };
  *waveRam->getLocation(0xFF38) = std::uint8_t { 0xAF };
  *waveRam->getLocation(0xFF39) = std::uint8_t { 0xFA };
  *waveRam->getLocation(0xFF3A) = std::uint8_t { 0x00 };
  *waveRam->getLocation(0xFF3B) = std::uint8_t { 0xAF };
  *waveRam->getLocation(0xFF3C) = std::uint8_t { 0xFA };
  *waveRam->getLocation(0xFF3D) = std::uint8_t { 0x00 };
  *waveRam->getLocation(0xFF3E) = std::uint8_t { 0xAF };
  *waveRam->getLocation(0xFF3F) = std::uint8_t { 0xFA };
  GbChannel3 c(nr30, nr31, nr32, nr33, nr34, nr52, waveRam);

  AudioFile<double> a {};
  a.setBitDepth(16);
  a.setNumChannels(1);
  a.setSampleRate(44100);
  a.setNumSamplesPerChannel(1.5 * 44100);

  auto frameSequencer = 0U;
  for (auto i = 0U; i < 1048576; ++i) {
    c.clock();
    if (i % (1048576 / 44100) == 0) {
      a.samples[0][i / (1048576 / 44100)] = c.getSample();
    }
    if ((i & 0b111111111111U) == 0b100000000000U) {
      c.tickApuDiv(static_cast<FrameSequence>(frameSequencer++));
      if (frameSequencer > 7U) {
        frameSequencer = 0U;
      }
    }
    if (i == (1048576 / 4)) {
      nr32->set(0b01000000U);
    }
    if (i == (1048576 / 2)) {
      nr32->set(0b00100000U);
    }
    if (i == ((1048576 * 3) / 4)) {
      nr32->set(0b00000000U);
    }
  }
  a.save("bla4.wav");
}
