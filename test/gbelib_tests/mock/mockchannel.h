#ifndef MOCKCHANNEL_H
#define MOCKCHANNEL_H

#include "apu/channel.h"

#include "mockregisteradapter.h"

class MockChannel : public Channel {
public:
  MockChannel()
      : Channel(MockRegisterAdapter::make(0b11111111U))
  {
  }

  void clock() override { }
  void tickApuDiv(const FrameSequence sequence) override { (void)sequence; }
  void disable() override { }

  static ChannelSP make() { return std::make_shared<MockChannel>(); }
};

#endif // MOCKCHANNEL_H
