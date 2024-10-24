#ifndef IAPU_H
#define IAPU_H

#include <memory>

#include "defines.h"

class IApu {
public:
  virtual ~IApu() = default;
  DISABLE_COPY_AND_MOVE(IApu)

  virtual void clock() = 0;

protected:
  IApu() = default;
};

using IApuUP = std::unique_ptr<IApu>;

#endif // IAPU_H
