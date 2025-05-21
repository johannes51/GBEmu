#ifndef IAPU_H
#define IAPU_H

#include <memory>

#include "defines.h"
#include "peripherals/tickable.h"

class IApu : public Tickable {
public:
  ~IApu() override = default;
  DISABLE_COPY_AND_MOVE(IApu)

  virtual const std::pair<double, double>& currentSample() = 0;

protected:
  IApu() = default;
};

#endif // IAPU_H
