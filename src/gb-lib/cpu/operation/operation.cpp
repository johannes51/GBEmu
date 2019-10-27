#include "operation.h"

#include "location/location.h"

Operation::Operation()
    : clocks_(0)
{
}

void Operation::clock()
{
  if (clocks_ == cycles()) {
    throw std::logic_error("Already done");
  }
  ++clocks_;
}

bool Operation::isDone() { return clocks_ == cycles(); }

void Operation::execute(RegistersInterface& registers, IMemoryView& memory)
{
  if (clocks_ != cycles()) {
    throw std::logic_error("Tried to execute operation that isn't done");
  }
  executeImpl(registers, memory);
}
