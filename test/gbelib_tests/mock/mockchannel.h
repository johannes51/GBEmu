#ifndef MOCKCHANNEL_H
#define MOCKCHANNEL_H

#include "apu/channel.h"

#include "mockregisteradapter.h"

static auto mockReg = MockRegisterAdapter::make(0b11111111U);

class MockChannel : public Channel {
public:
  MockChannel()
      : Channel(*mockReg)
  {
  }

  void clock() override { }
  void tickApuDiv(const FrameSequence sequence) override { (void)sequence; }
  void disable() override { }

  static ChannelUP make() { return std::make_unique<MockChannel>(); }
};

#endif // MOCKCHANNEL_H
