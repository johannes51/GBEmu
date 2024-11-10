#ifndef IPPU_H
#define IPPU_H

#include <memory>

#include "defines.h"
#include "irenderer.h"
#include "peripherals/tickable.h"

class IPpu : public Tickable {
public:
  ~IPpu() override = default;
  DISABLE_COPY_AND_MOVE(IPpu)

  virtual const GbPixelBuffer& getBuffer() const = 0;

protected:
  IPpu() = default;
};

using IPpuUP = std::unique_ptr<IPpu>;

#endif // IPPU_H
