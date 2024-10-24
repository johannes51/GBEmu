#ifndef IPPU_H
#define IPPU_H

#include <memory>

#include "defines.h"

class IPpu {
public:
  virtual ~IPpu() = default;
  DISABLE_COPY_AND_MOVE(IPpu)

  virtual void clock() = 0;

protected:
  IPpu() = default;
};

using IPpuUP = std::unique_ptr<IPpu>;

#endif // IPPU_H
