#ifndef IAPU_H
#define IAPU_H

#include <memory>

#include "defines.h"
#include "peripherals/tickable.h"

class IApu : public Tickable {
public:
  ~IApu() override = default;
  DISABLE_COPY_AND_MOVE(IApu)

protected:
  IApu() = default;
};

using IApuUP = std::unique_ptr<IApu>;

#endif // IAPU_H
