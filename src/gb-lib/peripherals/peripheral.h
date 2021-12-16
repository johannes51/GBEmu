#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "peri_defines.h"

class Peripheral {
public:
  virtual ~Peripheral() = default;

  virtual void clock() = 0;

protected:
  Peripheral() = default;
};

#endif // PERIPHERAL_H
