#include "operation.h"

#include "location/location.h"

Operation::Operation() : clocks_(0) {}

void Operation::clock() {
  if (clocks_ == cycles()) {
    throw std::logic_error("Already done");
  }
  ++clocks_;
}

bool Operation::isDone() { return clocks_ == cycles(); }
