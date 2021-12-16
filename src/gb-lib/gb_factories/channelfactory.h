#ifndef CHANNELFACTORY_H
#define CHANNELFACTORY_H

#include <vector>

#include "apu/ichannel.h"
#include "apuregisterfactory.h"
#include "mem/imemoryview.h"

class ChannelFactory {
public:
  explicit ChannelFactory(ApuRegisterFactory& registerFactory)
      : registerFactory_(registerFactory)
  {
  }

  std::vector<IChannelSP> constructChannels();

private:
  ApuRegisterFactory& registerFactory_;
};

#endif // CHANNELFACTORY_H
