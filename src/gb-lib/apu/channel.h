#ifndef CHANNEL_H
#define CHANNEL_H

#include <memory>

#include "channel_util/dac.h"
#include "channel_util/framesequencer.h"
#include "defines.h"
#include "mem/registers/iregisteradapter.h"

class Channel {
public:
  virtual ~Channel() = default;
  DISABLE_COPY_AND_MOVE(Channel)

  const double& getSample() const { return dac_.getSample(); }

  virtual void clock() = 0;
  virtual void tickApuDiv(const FrameSequence sequence) = 0;

  virtual void disable() { nr52_.setBit(1U, false); }

protected:
  explicit Channel(IRegisterAdapter& nr52)
      : nr52_(nr52)
  {
  }

  IRegisterAdapter& nr52_;
  DAC dac_;
};

using ChannelSP = std::shared_ptr<Channel>;

#endif // CHANNEL_H
