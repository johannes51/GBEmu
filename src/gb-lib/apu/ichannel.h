#ifndef ICHANNEL_H
#define ICHANNEL_H

#include <memory>

class IChannel {
public:
  virtual ~IChannel() = default;

protected:
  IChannel() = default;
};

using IChannelUP = std::unique_ptr<IChannel>;

#endif // ICHANNEL_H
