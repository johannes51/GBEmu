#ifndef INTERRUPTHANDLER_H
#define INTERRUPTHANDLER_H

#include <memory>

#include "cpu/operation/singleop.h"
#include "defines.h"

class InterruptHandler : public SingleOp<5> {
public:
  InterruptHandler() = default;
  DISABLE_COPY_AND_MOVE(InterruptHandler)
  ~InterruptHandler() override = default;

  virtual bool isInterrupt() const = 0;
};

using InterruptHandlerUP = std::unique_ptr<InterruptHandler>;

#endif // INTERRUPTHANDLER_H
