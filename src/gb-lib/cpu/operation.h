#ifndef OPERATION_H
#define OPERATION_H

#include <stdint.h>


class Operation
{
public:
  Operation(uint8_t value);

  const uint8_t& lowerNibble();
  const uint8_t& upperNibble();

private:
  const uint8_t value_;
  const uint8_t lower_;
  const uint8_t upper_;
};

#endif // OPERATION_H
