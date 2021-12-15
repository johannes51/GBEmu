#ifndef CHANNELFACTORY_H
#define CHANNELFACTORY_H

#include <vector>

#include "apu/ichannel.h"
#include "mem/imemoryview.h"

class ChannelFactory {
public:
  explicit ChannelFactory(IMemoryViewSP ioBank)
      : ioBank_(std::move(ioBank))
  {
  }

  std::vector<IChannelSP> constructChannels();

private:
  IMemoryViewSP ioBank_;
};

#endif // CHANNELFACTORY_H
