#ifndef IMIXER_H
#define IMIXER_H

#include <memory>

class IMixer {
public:
  virtual ~IMixer() = default;

protected:
  IMixer() = default;
};

using IMixerUP = std::unique_ptr<IMixer>;

#endif // IMIXER_H
