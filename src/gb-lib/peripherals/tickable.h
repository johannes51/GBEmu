#ifndef TICKABLE_H
#define TICKABLE_H

#include <memory>

#include "defines.h"

class Tickable {
public:
  virtual ~Tickable() = default;
  DISABLE_COPY_AND_MOVE(Tickable)

  virtual void clock() = 0;

protected:
  Tickable() = default;
};

using TickableUP = std::unique_ptr<Tickable>;

#endif // TICKABLE_H
